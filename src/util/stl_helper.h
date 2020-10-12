#pragma once

namespace sna {

template <typename T>
typename T::mapped_type get_or(const T& m,
                       const typename T::key_type& key,
                       const typename T::mapped_type& default_value) {
  auto it = m.find(key);
  if (it == m.end())
    return default_value;
  return it->second;
}

}  // namespace sna