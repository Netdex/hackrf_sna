# hackrf_sna

`This project is a work-in-progress.`

Scalar network analyzer using a mix and match of the following components:
- HackRF
- RTL2832 based receiver
- Directional coupler/RF bridge/return loss bridge
- Noise source
- Signal generator (HackRF/rpitx)

To get phase information you would need a full-duplex transceiver or another HackRF (and tie their clocks together).
I have none of those, so I'll leave that for the future.

## Road map
- Spectrum analyzer
    - RTL2832/HackRF
- Filter/amp analysis (two-port)
- VSWR/return loss analysis (multi-port)

- Scalar network analysis
    - Noise source reference
        - Noise generator -> DUT -> HackRF/RTL2832
    - Tracking generator reference 
        - HackRF/rpitx/... -> DUT -> HackRF/RTL2832

- Antenna analysis using RF Bridge/return loss bridge/directional coupler

## Build
This project builds `libhackrf` as a dependency. On Linux, you will need its dependencies installed on your system. Namely,
- libusb
- pthreads

On Windows, these libraries are prebuilt and included in the project. See [hackrf/Operating System Tips](https://github.com/mossmann/hackrf/wiki/Operating-System-Tips) for more details.

To build, execute the following commands:
```bash
git clone --recurse-submodules https://github.com/netdex/hackrf_sna.git
cd hackrf_sna
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j $(nproc) # or %NUMBER_OF_PROCESSORS% on Windows
```
