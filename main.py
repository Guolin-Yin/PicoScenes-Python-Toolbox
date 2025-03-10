# %%
from picoscenes import Picoscenes
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import savemat

def process_udp_stream(port=50000):
    # Initialize PicoScenes with empty file path
    scanner = Picoscenes()
    
    data = []
    # Start UDP listener
    try:
        print("Starting UDP listener on port", port)
        for frame in scanner.listen_udp(port):
            if frame and "BasebandSignals" in frame:
                # csi_data = frame["CSI"]
                baseband_data = frame["BasebandSignals"]
                print("Baseband signal shape:", baseband_data.shape)
                data.append(baseband_data)
                

                    # Save the collected baseband signals to a .mat file
    except KeyboardInterrupt:
        if len(data) > 0:
            savemat('baseband_signals.mat', {'baseband_data': data})
            print("\nSaved baseband signals to baseband_signals.mat")
        print("\nStopped UDP listener")
        return data

# %%
if __name__ == "__main__":
    data = process_udp_stream(50000)
    print("Received", len(data), "frames")
# %%
