# OS in 1,000 Lines: RISC-V Microkernel (Work in progress)

## 📖 Overview

**OS in 1,000 Lines** is a bare-metal operating system implementation targeting the **RISC-V** architecture.

The goal is to construct a minimal, functional kernel that can boot, manage processes, and handle system calls.

Currently this is a WIP project, and is allowing me to get more confident with the whole boot process of the linux kernel, the privileged instructions of risc-v, process scheduler. My goal is to not only follow the guide, but add more functionalities and improve the base OS.
## 🛠 Core Concepts & Implementation

This kernel operates in **Supervisor Mode (S-Mode)**, interacting with the **SBI (Supervisor Binary Interface)** provided by OpenSBI.

### 1. Boot Process & ABI

* **Linker Script (`kernel.ld`):** Manually defines the memory layout (`.text`, `.data`, `.bss`) to ensure the kernel is loaded at the correct physical address (`0x80200000`).
* **Entry Point (`boot.S`):** Assembly code that sets up the stack pointer (`sp`) and jumps to C code (`kernel_main`).

### 2. Kernel Panic & Exceptions

* **Trap Handling (`stvec`):** Direct manipulation of Control and Status Registers (CSRs) to catch exceptions and interrupts.
* **Exception Vectors:** Handling synchronous exceptions (like illegal instructions) and asynchronous interrupts (timer).

### 3. Process Management

* **Context Switching:** Saving and restoring register states (`ra`, `sp`, `s0-s11`) to switch between processes.
* **Round-Robin Scheduler:** A cooperative multitasking scheduler that yields CPU time between user tasks.
* **Process Control Block (PCB):** Structure defining the state of a process (PID, stack pointer, state).

### 4. Memory Management

* **Page Tables (SV32):** Implementing virtual memory mapping using Root Page Tables.
* **Memory Allocation:** A simple bump pointer allocator to manage physical pages.

### 5. Input/Output

* **VirtIO:** Drivers to communicate with virtual block devices (disk).
* **UART/SBI Console:** implementing `putchar` and `getchar` via SBI calls for console output.

## 🏗 Architecture Flow

1. **Power On (M-Mode):** QEMU/Hardware loads OpenSBI.
2. **Jump to Kernel (S-Mode):** OpenSBI jumps to our `0x80200000` entry point.
3. **Kernel Init:** Setup memory paging, trap vectors, and process structures.
4. **User Mode (U-Mode):** The kernel uses `sret` to drop privileges and execute user applications.
5. **System Calls (`ecall`):** User applications request services, trapping back into the kernel.

## 🚀 Build & Run

### Prerequisites

* **QEMU:** `qemu-system-riscv32`
* **Toolchain:** `clang` (with RISC-V support) or `riscv64-unknown-elf-gcc`

### Building the Kernel

To compile the kernel and generate the ELF binary:

```bash
./run.sh

```
*( The `run.sh` script handles compilation via clang and launches QEMU ).*

### Debugging

To run QEMU in debug mode you can refer to this guide: https://en.wikibooks.org/wiki/QEMU/Debugging_with_QEMU

## 👨‍💻 Author

**Sergi Juarez** *Systems Software Engineer | RISC-V & Kernel Enthusiast*

* **GitHub:** [imserez](https://github.com/imserez)
* **LinkedIn:** [sergijuarez](https://www.linkedin.com/in/sergijuarez)


---

*Based on the "Operating System in 1,000 Lines" challenge.*
https://operating-system-in-1000-lines.vercel.app/en/

