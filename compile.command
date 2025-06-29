#!/bin/bash
cd "$(dirname "$0")"
python3 utils/op_enums.py
docker run -v "$(pwd)":/target -t dewb/monome-build

# Check if teletype.zip was created
if [ -f "teletype.zip" ]; then
    # Remove old fw folder if it exists
    rm -rf fw

    # Unzip into 'fw' folder
    mkdir fw
    unzip -q teletype.zip -d fw

    # Delete the zip file
    rm teletype.zip

    # Open a new Terminal window at the fw folder
    open -a Terminal "$PWD/fw"
else
    echo "teletype.zip not found. Something went wrong."
    exit 1
fi