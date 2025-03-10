# Picoscenes Toolbox

This project is a fork of the [PicoScenes-Python-Toolbox](https://github.com/wifisensing/PicoScenes-Python-Toolbox), a Python toolbox for parsing `.csi` files generated by PicoScenes. It has been enhanced to support both real-time UDP streaming and offline file analysis.

## Features

- **Real-time UDP Mode**: Listen to UDP packets and process CSI data in real-time.
- **Offline File Mode**: Read and analyze CSI data from pre-recorded `.csi` files.

## Recent Changes

1. **Dual Mode Support**: The `Picoscenes` class has been updated to support both real-time UDP streaming and offline file reading. The `file` parameter is now optional, allowing the class to be initialized without a file for real-time streaming.


## Usage

### Real-time UDP Mode

To use the Picoscenes class for real-time UDP streaming, initialize it without a file path. This mode listens on a specified port and processes incoming CSI data. Note that this functionality requires integration with the UDP forwarder plugin from the PicoScenes Plugin Development Kit (PDK). For more details, refer to the [PicoScenes-PDK repository](https://github.com/wifisensing/PicoScenes-PDK).

```python
from picoscenes import Picoscenes

# Initialize for real-time UDP streaming
udp_scanner = Picoscenes()  # or Picoscenes("")

# Listen on port 50000 and process frames
for frame in udp_scanner.listen_udp(50000):
    process_frame(frame)
```


This section now includes a reference to the PicoScenes-PDK, indicating the need for the UDP forwarder plugin to enable real-time streaming functionality.

### Offline File Mode

To analyze pre-recorded CSI data, initialize the Picoscenes class with the path to a `.csi` file. This mode reads the file and allows you to process each frame.

```python
from picoscenes import Picoscenes

# Initialize for offline file analysis
file_scanner = Picoscenes("data.csi")

# Process each frame in the file
for frame in file_scanner.raw:
    analyze_frame(frame)
```

## Example Script

The `main.py` script demonstrates how to use the Picoscenes class in real-time UDP mode. It listens on port 50000, collects baseband signals, and saves them to a `.mat` file upon termination.

```python
from picoscenes import Picoscenes
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import savemat

def process_udp_stream(port=50000):
    scanner = Picoscenes()
    data = []
    try:
        print("Starting UDP listener on port", port)
        for frame in scanner.listen_udp(port):
            if frame and "BasebandSignals" in frame:
                baseband_data = frame["BasebandSignals"]
                print("Baseband signal shape:", baseband_data.shape)
                data.append(baseband_data)
    except KeyboardInterrupt:
        if len(data) > 0:
            savemat('baseband_signals.mat', {'baseband_data': data})
            print("\nSaved baseband signals to baseband_signals.mat")
        print("\nStopped UDP listener")
        return data

if __name__ == "__main__":
    data = process_udp_stream(50000)
    print("Received", len(data), "frames")
```

## Installation

1. Clone this repository with the `--recursive` option.

```bash
git clone https://github.com/Herrtian/PicoscenesToolbox.git --recursive
```

2. Install Python and dependencies.

```bash
sudo apt update
sudo apt install python3
sudo apt install python3-pip
```

* If you are a **Chinese** user, you can change the pip source to accelerate download speed.

```bash
pip config set global.index-url https://mirrors.aliyun.com/pypi/simple/
```

* Install dependencies.

```bash
pip3 install -r requirements.txt
```

3. Build the program.

```bash
python3 setup.py build_ext --inplace
```

## Reference Links

* **[PicoScenes](https://ps.zpj.io/)**: A powerful Wi-Fi sensing platform middleware for a wide range of hardware.
  * This project was released by [Zhiping Jiang](https://zpj.io/bio/).


## Acknowledgments

This project is a fork of the [PicoScenes-Python-Toolbox](https://github.com/wifisensing/PicoScenes-Python-Toolbox), and we thank the original authors for their work.