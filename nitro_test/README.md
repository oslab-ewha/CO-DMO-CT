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
    


