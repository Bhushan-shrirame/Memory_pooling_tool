
# **Trace-Based Simulations for Disaggregated Memory Systems**

## **1. Setup Instructions:**

### **Step 1: Download DRAMSim2**
* Download DRAMSim2 from **https://github.com/umd-memsys/DRAMSim2**
- Download the DRAMSim2 package in your working directory.

### **Step 2: Apply Patch**
- Navigate to the DRAMSim2 directory.
- Apply the patch using the following command:
  ```bash
  patch -p1 < DRAMSim2.patch
  ```

### **Step 3: Build DRAMSim2**
- Build DRAMSim2 using the following command:
  ```bash
  cd DRAMSim2
  make libdramsim.so
  cd ..
  ```
- make executable of DRackSim name it TrackDRackSim using make commmand
### **Step 4: Update ini Directory**
- Copy all files from the `DRAMSim2_ini` directory to the `ini` directory inside `DRAMSim2/ini`.

---

## **2. Running Trace-Based Simulation**


### **Step 1: Trace Production**
***Installing Pin***
* Download pin-3.30-98830-g1d7b601b3-gcc-linux.tar.gz from 

https://www.intel.com/content/www/us/en/developer/articles/tool/pin-a-binary-instrumentation-tool-downloads.html


1. Copy the `DRackSim-Trace` directory to your Pin tool path. The directory should be placed inside:
   ```bash
   pin-path/source/tools
   ```
  5. Install Boost Libraries
   - Download Boost or use the provided copy.
   - Extract it into the following directory:
     ```bash
     $pin-path/source/include/pin/
     ```
2. Run `make` in pin-path/source/tools to compile the pintool.

3. Copy all the files inside the `Trace_tool` directory into the main directory (similar to the DRAMSim-Trace folder).

4. Navigate to the `DRAMSim-Trace` directory:
   ```bash
   cd DRAMSim-Trace
   ```

6. Create obj-intel64 folder in $pin-path/source/tools/DRackSim-Trace/

7. Run the following command to build the memory trace tool:
   ```bash
   make obj-intel64/Mem_Trace.so TARGET=intel64
   ```

8. Create an executable of the program you want to trace, for example, matrix multiplication or any other file:
   - Compile the program (e.g., `example.cpp`) using g++ or your preferred compiler to produce an executable:
     ```bash
     g++ example.cpp -o example.out
     ```

9. Generate the trace by running the Pin tool along with the memory trace tool:
   ```bash
   ../../pin -t obj-intel64/Mem_Trace.so -P 1 -N 1 -T 0 -- ./example.out
   ```

10. Once the trace is generated, an output folder will be created containing the trace files.

### **Step 2: Parse Trace Files**

1. Compile the `parse_trace.cpp` file:
   ```bash
   g++ parse_trace.cpp -o parse_trace
   ```

2. Run the parser to create the parsed trace:
   ```bash
   ./parse_trace
   ```

   - This will generate the `Parsed_Trace_Node1.trc` file.

---

## **3. Running Disaggregated Memory Simulation**

1. Ensure you have an executable for DRackSim.

2. Run the simulation using the following command:
   ```bash
   ./TrackDRackSim <any-folder-name>
   ```

   - All the simulation statistics will be saved inside the specified folder.

---
 
