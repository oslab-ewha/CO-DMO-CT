# CO-DMO-CT (Co-optimization of DVS, Memory placement, and Offloading with compatible TEE)

This project implements real-time task scheduling using steady-state genetic algorithms to minimize power consumption in CPU, memory, and network subsystems while meeting deadline constraints.

CO-DMO-CT integrates three energy-saving techniques across different system layers:
- DVS (Dynamic Voltage Scaling): Adjusting voltage and frequency to reduce CPU power consumption.

- Persistent Memory Placement: Optimizing data placement to minimize memory energy usage.

- Task Offloading: Executing tasks on edge servers that support a Trusted Execution Environment (TEE) to ensure secure execution.

Two executables included in this project, which can simulate CO-DMO-CT in comparison with DVS, Offloading, and basic configurations.
- `gasgen`: task generation tool based on CPU and total utilization
- `gastask`: scheduling scheme generator based on GA


## Build
To build `gastask` and `gasgen`, use CMake:
```
$ mkdir -p build && cd build
$ cmake ..
$ make
```

## Run
- Create a new configuration file. Refer to `gastask.conf.tmpl`.
- run `gasgen`
```
# ./gasgen gastask.conf
```
- Tasks list will be generated into <code>task_generated.txt</code> <code>network_generated.txt</code> <code>network_commander_generated.txt</code>according to gastask.conf
- paste <code>task_generated.txt</code> into the task section of gastask.conf 
- paste <code>network_generated.txt</code> into the network section of gastask.conf
- paste <code>network_commander_generated.txt</code> into the net_commander_ section of gastask.conf
- run gastask
```
# ./gastask gastask.conf
```
- scheduling information is generated in <code>task.txt</code>, which can be used as an input to simrts.

## CO-DMO-CT: IIoT Application Offloading with AWS Nitro Enclaves

This project demonstrates how to securely offload Industrial IoT (IIoT) application tasks to a Trusted Execution Environment (TEE) using AWS Nitro Enclaves.

### System Overview
- **IIoT Device**: Simulates a constrained edge device generating tasks that can be either locally executed or offloaded.
- **Gateway**: Receives IIoT tasks and forwards them to the enclave.
- **Enclave**: Executes the offloaded computation securely within the Nitro Enclave. Currently, the enclave implementation simply prints a basic message to demonstrate successful offloading.

---

### 1. Prepare IIoT and Enclave Code

- Modify `iiot_device.c` for IIoT task logic. This code can execute either locally or be offloaded to the enclave, depending on system configuration.
- Implement the offloaded logic in `enclave.c`. The same computation code may exist in both components, enabling flexible offloading.
- Add any required libraries to `CMakeLists.txt`.

---

### 2. Build the System Components

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```
This builds the following binaries:
- `iiot_device`: IIoT device emulator that generates tasks.
- `gateway`: Forwards tasks from the IIoT device to the enclave.
- `enclave`: Executes offloaded tasks inside the TEE (Nitro Enclave).

---

### 3. Build the Enclave Image

```sh
$ ./build_enclave.sh
```
This script generates the Enclave Image File (EIF) using a Docker-based build process:

1. A Docker container is created based on the provided `Dockerfile.ne`, which defines the enclave runtime environment.
2. The Docker image includes the following required files:
   - `libnsm.so`: The Nitro Secure Module library for enclave-host communication.
   - `enclave`: The compiled binary that executes within the enclave.
   - `bootstrap.sh`: An entrypoint script for enclave execution.
3. The container is then converted into an EIF using `nitro-cli build-enclave`.

Ensure that `Dockerfile.ne` and all required files are located in the correct context directory when running the build script.

---

### 4. Launch Gateway and Enclave

In one terminal:
```sh
$ ./gateway
```
In another terminal:
```sh
$ ./run_enclave.sh
```
This script launches the Nitro Enclave using the EIF created earlier.

---

### 5. Run the IIoT Emulator

```sh
$ ./iiot_device -g <gateway_ip>
```
This simulates IIoT task generation and sends tasks to the gateway for secure offloading.

If successful, the terminal will display logs confirming secure transmission and execution.

---

### Notes
- Make sure your EC2 instance supports Nitro Enclaves.
- Ensure required permissions and enclave-enabled AMI settings are configured.
- Refer to AWS Nitro Enclaves documentation for detailed enclave configuration.