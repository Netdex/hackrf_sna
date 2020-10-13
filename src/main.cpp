#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glog/logging.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include "gui/device_picker.h"
#include "gui/imgui_functor.h"
#include "gui/sna_workspace.h"
#include "util/config.h"

static void glfw_error_callback(int error, const char* description) {
  LOG(ERROR) << "GLFW error " << error << ": " << description;
}

int main(int, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  // google::InstallFailureSignalHandler();
  FLAGS_logtostderr = true;
  FLAGS_colorlogtostderr = true;
  FLAGS_minloglevel = 0;
  // FLAGS_v = 2;

  auto& config = sna::GetConfig();

  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  CHECK(glfwInit());

  // GL 3.3 + GLSL 330
  const char* glsl_version = "#version 330 core";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  // Create window with graphics context
  GLFWwindow* window =
      glfwCreateWindow(1280, 720, "HackRF Scalar Network Analyzer", NULL, NULL);
  if (window == NULL)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Remember window location
  int width, height, xpos, ypos;
  glfwGetWindowPos(window, &xpos, &ypos);
  glfwGetWindowSize(window, &width, &height);
  toml::value window_rect = toml::find_or(
      config, "window",
      toml::table{{{"x", xpos}, {"y", ypos}, {"w", width}, {"h", height}}});
  // We need to set window position twice to support multi-DPI configurations.
  glfwSetWindowPos(window, toml::find<int>(window_rect, "x"),
                   toml::find<int>(window_rect, "y"));
  glfwSetWindowPos(window, toml::find<int>(window_rect, "x"),
                   toml::find<int>(window_rect, "y"));
  glfwSetWindowSize(window, toml::find<int>(window_rect, "w"),
                    toml::find<int>(window_rect, "h"));
  glfwShowWindow(window);

  CHECK(gladLoadGL()) << "Failed to initialize OpenGL loader!";

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;            // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking

  ImGui::StyleColorsDark();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // TODO Make this configurable
  style.ScaleAllSizes(2.f);
  io.Fonts->AddFontFromFileTTF("res/RobotoCondensed-Regular.ttf", 24.0f);

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  auto device_picker = std::make_shared<sna::DevicePicker>();
  auto demo_window =
      std::make_shared<sna::ImGuiFunctor>([&](sna::ImGuiFunctor&) {
        if (show_demo_window) {
          ImGui::ShowDemoWindow(&show_demo_window);
          ImPlot::ShowDemoWindow(&show_demo_window);
        }

        {
          static float f = 0.0f;
          ImGui::Begin("Hello, world!");
          ImGui::Text("This is some useful text.");
          ImGui::Checkbox("Demo Window", &show_demo_window);
          ImGui::Checkbox("Another Window", &show_another_window);
          ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
          ImGui::ColorEdit3("clear color", (float*)&clear_color);

          if (ImGui::Button("Button")) {
            device_picker->ShowModal();
          }

          ImGui::SameLine();
          ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                      1000.0f / ImGui::GetIO().Framerate,
                      ImGui::GetIO().Framerate);
          ImGui::End();
        }

        if (show_another_window) {
          ImGui::Begin("Another Window", &show_another_window);

          ImGui::Text("Hello from another window!");
          if (ImGui::Button("Close Me"))
            show_another_window = false;
          ImGui::End();
        }
      });

  sna::SnaWorkspace dockspace;
  dockspace.AddChildren({device_picker, demo_window});
  dockspace.RegisterEventHandler<sna::CancelledEvent>(
      [window](const sna::CancelledEvent&) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      });

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    dockspace.Process();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  // Save configuration
  glfwGetWindowPos(window, &xpos, &ypos);
  glfwGetWindowSize(window, &width, &height);
  config["window"] =
      toml::table{{{"x", xpos}, {"y", ypos}, {"w", width}, {"h", height}}};
  sna::SaveConfig();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
