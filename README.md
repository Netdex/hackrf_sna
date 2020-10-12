# hackrf_sna

[![CMake](https://github.com/Netdex/hackrf_sna/workflows/CMake/badge.svg)](https://github.com/Netdex/hackrf_sna/actions?query=workflow%3ACMake)

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

## Known Issues
### Debug build crashes on startup
SoapySDR has ABI incompatibility on Windows between Debug and Release builds.
Since your PothosSDR release was probably built in Release mode, you must
build this project with RelWithDebInfo or Release modes, or build SoapySDR in
Debug mode.

### Program crashes intermittently during device enumeration
It seems like [at least one of the SoapySDR modules is
buggy](https://github.com/pothosware/SoapyRTLSDR/issues/38). My guess is that
there is some contention with LibUSB between multiple support modules. A
stopgap measure is to disable all modules you do not need, you can do this on
Windows by going to `C:\Program Files\PothosSDR\lib\SoapySDR\modules0.8` and
deleting/moving DLLs which are not necessary for your setup.

## Build
This project requires
[PothosSDR](https://github.com/pothosware/PothosCore/wiki/Downloads)
installed on your machine, which provides support libraries for various SDR
hardware and SoapySDR. For the exact list of dependencies required, see the
[CI
configuration](https://github.com/Netdex/hackrf_sna/blob/master/.github/workflows/cmake.yml).

To build, execute the following commands:
```bash
git clone --recurse-submodules https://github.com/netdex/hackrf_sna.git
cd hackrf_sna
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j $(nproc) # or %NUMBER_OF_PROCESSORS% on Windows
```
