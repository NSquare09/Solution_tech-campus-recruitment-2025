# **Discussion.md**

## **Solutions Considered**

### **1. Line-by-Line Processing**
- **Approach:** Read the log file line by line and filter entries matching the specified date.
- **Advantages:**
  - Memory-efficient, as only one line is loaded into memory at a time.
  - Works well for large files, even those around 1 TB.
- **Disadvantages:**
  - Sequential reading can be slower than more advanced methods.

### **2. Indexing**
- **Approach:** Create an index file mapping dates to file offsets. Use the index to quickly locate relevant portions of the log file.
- **Advantages:**
  - Extremely fast lookups once the index is built.
- **Disadvantages:**
  - Indexing requires additional storage.
  - Building the index for a 1 TB file can be time-consuming initially.
  - This approach is best suited for repeated queries on the same file.

### **3. Parallel Processing**
- **Approach:** Divide the file into smaller chunks, process each chunk in parallel to filter relevant entries, and merge the results.
- **Advantages:**
  - Utilizes multiple CPU cores to speed up processing.
  - Effective for systems with high-performance I/O.
- **Disadvantages:**
  - Complex to implement, especially for ensuring accurate splitting without breaking log entries.
  - Requires merging results, which adds an extra step.

---

## **Final Solution Summary**

We chose **line-by-line processing** because:
1. **Simplicity:** It is straightforward to implement and does not require complex indexing or parallelism.
2. **Memory Efficiency:** The solution processes one line at a time, making it suitable for very large files.
3. **Portability:** This approach works reliably across systems without additional dependencies.
4. **Alignment with Constraints:** It meets the problem's constraints for efficient time and resource utilization.

The solution reads the input file line-by-line, compares each line's timestamp prefix to the given date, and writes matching lines to the output file. This ensures that the program works efficiently even for a file size of 1 TB.

---

## **Steps to Run**

### **1. Compile the Program**
Ensure you have a C compiler installed. Use the following command to compile the program:
```bash
gcc extract_logs.c -o extract_logs
```
### **2. Prepare Input**
Download the large log file using the given URL:
```bash
https://limewire.com/d/90794bb3-6831-4e02-8a59-ffc7f3b8b2a3#X1xnzrH5s4H_DKEkT_dfBuUT1mFKZuj4cFWNoMJGX98
```
This command will download the log file and save it as test_logs.log in your current directory.


### **3. Run the Program**
Run the compiled executable with the log file and the desired date (YYYY-MM-DD) as arguments:
```bash
./extract_logs test_logs.log 2024-12-01
```
Replace 2024-12-01 with any date you'd like to extract logs for. This command will filter the logs for the specified date from the test_logs.log file and save the matching entries to an output file.

### **4. Output Location**
The filtered logs will be saved in the output directory. The output file will be named as output/output_YYYY-MM-DD.txt.
```bash
output/output_2024-12-01.txt
```
The output file will contain all the logs from test_logs.log that match the specified date (2024-12-01).



