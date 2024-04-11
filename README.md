# EDA-Course: Computing Machine

## Overview
This project is a simulation of a computing machine. The architecture includes core components such as RAM, a BUS and a CPU.
## Architecture
- **RAM**
- **CPU**
- **BUS**: Consisting of:
    - **MUX**
    - **DEMUX**
    - **Arbiter**
    - **Dispatcher**
- **VGA (Optional)**

## Building the Simulation
To build the simulation, follow these steps:

1. Create a build directory.
2. Change into the build directory.
3. Use the make command to compile the project.
4. After compilation, return to the project root directory.


```bash
mkdir build
cd build
make
cd ../
```
    

## Usage
To run the simulation, use the following command from the project root directory:
```bash
 ./build/EDA_course <file_path>
```

You can use [gcd.txt](gcd.txt) file which contains the necessary instructions or data for GCD algorithm and the result get as an output.
