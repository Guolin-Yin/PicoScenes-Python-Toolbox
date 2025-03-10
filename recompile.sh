#!/bin/bash

# Exit on error
set -e

echo "Uninstalling existing picoscenes package..."
pip uninstall -y picoscenes || true

echo "Building package in-place..."
python3 setup.py build_ext --inplace

echo "Installing package in editable mode..."
pip install -e .

echo "Recompilation complete!"