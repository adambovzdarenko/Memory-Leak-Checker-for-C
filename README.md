# Memory Leak Detector for C Scripts

This program checks C source files for potential memory leaks by analyzing `malloc` and `free` calls. It scans the script line by line, skipping comments, and reports any imbalances between memory allocations (`malloc`) and deallocations (`free`).

## Features
- **Comment Handling:** Ignores comments, including single-line (`//`) and multi-line (`/* */`) comments, during memory leak analysis.
- **Line-by-Line Analysis:** Scans each line for `malloc` and `free` calls while considering only the code portion, even if a comment appears after the function calls.
- **Memory Leak Detection:** Reports if the number of `malloc` calls exceeds `free` calls, indicating potential memory leaks.

## How to Use

1. **Prepare Your C Script:**
   Ensure your C script contains `malloc` and `free` calls. The program will process the script and check for memory leaks.

2. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/memory-leak-detector.git
   cd memory-leak-detector
   ```

3. **Compile the Program:**
   Compile the program using `gcc`:
   ```bash
   gcc memory_leak_detector.c -o memory_leak_detector
   ```

4. **Run the Program:**
   Execute the program:
   ```bash
   ./memory_leak_detector
   ```

   The program will prompt you to enter the name of the C script you wish to analyze. For example:
   ```
   Enter the name of the C script to check for memory leaks: example.c
   ```

5. **Review the Output:**
   The program will scan your C script and output results indicating where `malloc` and `free` calls occur, and whether there are any mismatches suggesting potential memory leaks.

## Example

**Input:**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(sizeof(int) * 10);  // Allocated memory
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    free(arr);  // Freed memory

    malloc(20 * sizeof(int));  // Allocated but not freed
    malloc(50 * sizeof(int));  // Allocated but not freed

    return 0;
}
```

**Output:**

```
Enter the name of the C script to check for memory leaks: example.c
Found malloc at line 6:       int *arr = malloc(sizeof(int) * 10);  // Allocated memory
Found free at line 9:         free(arr);  // Freed memory
Found malloc at line 12:      malloc(20 * sizeof(int));  // Allocated but not freed
Found malloc at line 13:      malloc(50 * sizeof(int));  // Allocated but not freed

Warning: Potential memory leak detected! (3 malloc calls, 1 free calls)
```

## How It Works

- The program reads the C script line by line.
- It splits each line into the code and comment parts (if any).
- It counts the occurrences of `malloc` and `free` calls.
- It checks if the number of `malloc` calls is greater than the number of `free` calls, indicating a potential memory leak.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```

### Key Points:
- **Repository URL:** Replace `https://github.com/yourusername/memory-leak-detector.git` with the correct URL of your repository.
- **License:** The license section is using the MIT License, but feel free to update it based on your actual project license.
