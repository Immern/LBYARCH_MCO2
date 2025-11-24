# x86-to-C Interface Programming Project
This project was made following the LBYARCH MCO2 specs on comparing the run time of 2 versions of kernels: C and x86-64 on calculating the vector distance of 2 vectors containing float values by utilizing Scalar SIMD instructions. 

# Comparative Execution
The execution of both kernel versions was run 30 times for each input size to determine the average execution time. For the largest input size, the project used 2^26, as any higher input could not be handled by the machine. For the values, different vector data was used for each input size, wherein it was randomized based on the following seeds: 20, 24, 26. Shown below is a summary of the average run time of the two kernels for the given input sizes. 

| Input Size | C Kernel Execution Time(s)       | x86-64 Kernel Execution Time(s)  |
| ---------- | -------------------------- | -------------------------- |
| 2^20       | 0.027900                   | 0.003567                   |
| 2^24       | 0.298700                   | 0.046100                   |
| 2^26       | 2.369367                   | 0.281100                   |

For all average execution times, the x86-64 Kernel ran faster compared to the C Kernel by approximately 7.82, 6.48, and 8.43 times, respectively. Given this overview, there seems to be no huge relationship on how the input size correlates with how much faster the x86-64 runs compared to the C kernel; however, it must be considered that this has only been tested across the three input sizes and may need further investigation with smaller input sizes. With regards to why the x86-64 version of the kernel ran faster on average compared to the C version of the kernel, it is likely attributed to the use of scalar SIMD instructions such as  `movss`, `subss`, `mulss`, `addss`, and `sqrtss`, as well as the `xmm` registers. In addition to this, the optimal use of registers can be handled or manipulated by the programmer, whereas they can specify which data will be stored in the non-volatile and volatile registers, allowing for efficient manipulation of data and operands. Overall, the project was able to succeed in investigating the benefits of using an ASM kernel to get better performance. 

# Program Output for C Version
<img width="1534" height="719" alt="image" src="https://github.com/user-attachments/assets/014bd849-7152-4b4b-8350-f749a3f74140" />
Figure 1: Output of the C Kernel for an input size of 2^20 generated from the seed: 20.

<img width="1530" height="711" alt="image" src="https://github.com/user-attachments/assets/f8b639f8-987a-4b11-abaa-84572e070054" />
Figure 2: Output of the C Kernel for an input size of 2^24 generated from the seed: 24.

<img width="1541" height="713" alt="image" src="https://github.com/user-attachments/assets/d529c12b-fdc1-4662-96ac-feb112168104" />
Figure 3: Output of the C Kernel for an input size of 2^26 generated from the seed: 26.


# Program Output for x86-64 Output

<img width="1566" height="717" alt="image" src="https://github.com/user-attachments/assets/871b4817-76a8-4561-82d6-fcafb960f802" />
Figure 4: Output of the x86-64 Kernel for an input size of 2^20 generated from the seed: 20.


<img width="1559" height="715" alt="image" src="https://github.com/user-attachments/assets/e33caba1-f70a-4081-a1dd-42a7461bc297" />
Figure 5: Output of the x86-64 Kernel for an input size of 2^24 generated from the seed: 24.

<img width="1561" height="713" alt="image" src="https://github.com/user-attachments/assets/6fca8d4c-587c-4d48-a92a-553189e8a1f6" />
Figure 6: Output of the x86-64 Kernel for an input size of 2^26 generated from the seed: 26.

# Video Demo
https://drive.google.com/file/d/18f8yvp5i5q1z7ZgnzDe6PeXZEjuh3nzP/view?usp=sharing

# Setup
```bash
git clone https://github.com/Immern/LBYARCH_MCO2.git
cd LBYARCH_MCO2
build
```
