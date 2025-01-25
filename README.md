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

## Build TEE Environments via AWS Nitro Enclaves

### Setup an EC2 instance to support nitro enclave

1. Create an EC2 instance with Nitro Enclave enabled. An instance under Intel or AMD requires 4 vCPUs and 8GB of memory.
   Instance types such as m5.xlarge or m6i.xlarge should be sufficient. 
   The c6g.large AWS Graviton instance failed to work with Nitro Enclaves. The reason is currently unknown.

2. Start the EC2 instance.

3. Install the Nitro Enclaves CLI and development tools on Linux. 

4. Edit `/etc/nitro_enclaves/allocator.yaml` to ensure the memory size is at least 4GB.

## Build CO-DMO-CT(IIoT on TEE) Platform
1. **Prepare code for IoT device**

   The IoT code will be contained in iot_device.c. The same file will also be used for offloading.  
   If additional libraries or files are required, modify CMakeLists.txt accordingly.
   
2. **Build CO-DMO-CT enclave server and IIoT emulator**
   ```sh
   $ mkdir build
   $ cd build
   $ cmake ..
   ```

3. **Run the Enclave server**
   ```sh
   $ ./enclave_server
   ```
   
4. **Run the IIoT emulator**
   ```sh
   $ ./iiot_emulator <server ip> [<task option>]
   ```
   If successful, the command will output offloading information.
    


