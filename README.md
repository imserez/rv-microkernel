# OS in 1,000 Lines – RISC-V Microkernel (Work in Progress)

## Overview

This repository contains my implementation of a **minimal educational microkernel for the RISC-V architecture**.

The project explores how a kernel interacts directly with the hardware by implementing core operating system mechanisms such as:

- the **boot process**
- **trap handling**
- **process scheduling**
- **virtual memory management**
- **system calls**

The goal is to better understand the **interaction between processor architecture and operating system design**, particularly in the **RISC-V privilege model**.

The project is currently **work in progress** and follows the *Operating System in 1,000 Lines* guide while extending it with additional experiments and improvements.

---

# System Architecture

The kernel runs in **Supervisor Mode (S-Mode)** on top of **OpenSBI**, which provides machine-level services for RISC-V platforms.

Execution flow:

1. **Power On (M-Mode):** QEMU/Hardware loads OpenSBI.
2. **Jump to Kernel (S-Mode):** OpenSBI jumps to our `0x80200000` entry point.
3. **Kernel Init:** Setup memory paging, trap vectors, and process structures.
4. **User Mode (U-Mode):** The kernel uses `sret` to drop privileges and execute user applications.
5. **System Calls (`ecall`):** User applications request services, trapping back into the kernel.

User applications interact with the kernel through **system calls (`ecall`)**, which trigger traps handled by the kernel.

---

# Kernel Components

## Boot Process

The kernel boot sequence is implemented manually to understand the low-level initialization of a RISC-V system.

### Linker Script (`kernel.ld`)

Defines the kernel memory layout:

- `.text`
- `.data`
- `.bss`

The kernel is loaded at physical address 0x80200000


### Entry Point (`boot.S`)

Assembly code responsible for:

- initializing the stack pointer
- setting up the execution environment
- transferring control to the C kernel entry (`kernel_main`)

---

## Trap Handling

The kernel directly configures **RISC-V Control and Status Registers (CSRs)**.

Key mechanisms:

- `stvec` trap vector configuration
- exception handling
- interrupt handling

Supported events include:

- illegal instruction exceptions
- timer interrupts
- system call traps

---

## Process Management

The kernel implements a minimal **cooperative multitasking system**.

### Context Switching

Registers saved and restored during task switches: ra, sp, s0-s11


### Process Control Block (PCB)

Each process stores:

- process ID
- stack pointer
- execution state

### Scheduler

A simple **round-robin scheduler** distributes CPU time between tasks.

---

## Memory Management

The kernel experiments with **RISC-V SV32 virtual memory**.

Key mechanisms:

- page table setup
- address translation
- basic physical memory allocation

A simple **bump allocator** is used for early memory management.

---

## Input / Output

The kernel interacts with the system through **OpenSBI** and **VirtIO devices**.

### Console I/O

Implemented through SBI calls: putchar, getchar

### VirtIO

Used to experiment with block device communication in virtualized environments.

---

# Execution Flow

Kernel execution follows these steps:

1. **System Boot**

   QEMU loads **OpenSBI** in Machine Mode.

2. **Kernel Entry**

   OpenSBI jumps to the kernel entry point at 0x80200000

3. **Kernel Initialization**

- memory setup
- trap vector configuration
- process initialization

4. **User Mode Execution**

The kernel drops privileges using sret and starts executing user programs.

5. **System Calls**

Applications invoke kernel services via ecall which triggers a trap into the kernel.

---

# Build & Run

## Requirements

### QEMU

`qemu-system-riscv32`

### RISC-V Toolchain

clang` (with RISC-V support) or `riscv64-unknown-elf-gcc`

---

## Build and Execute

The project includes a helper script that builds the kernel and runs it inside QEMU.

```bash
./run.sh

```

The script:

1. compiles the kernel  
2. generates the ELF binary  
3. launches QEMU  

---

# Debugging

The kernel can be debugged using QEMU's debugging interface and GDB.

Reference guide:

https://en.wikibooks.org/wiki/QEMU/Debugging_with_QEMU

---

# Project Goals

This project is part of my learning path in:

- **Operating System design**
- **RISC-V privilege architecture**
- **low-level systems programming**
- **hardware / software interaction**

The goal is to understand how **kernels interact directly with processor architectures**, particularly in RISC-V systems.

---

# Future Work

Planned improvements include:

- expanding system call support
- improving memory management
- extending scheduler functionality
- implementing additional device drivers
- running more complex user applications

---

## Author

**Sergi Juarez**

* **GitHub:** [imserez](https://github.com/imserez)
* **LinkedIn:** [sergijuarez](https://www.linkedin.com/in/sergijuarez)

---
*Based on the "Operating System in 1,000 Lines" challenge.*
https://operating-system-in-1000-lines.vercel.app/en/

