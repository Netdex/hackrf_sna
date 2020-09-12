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
