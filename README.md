# Linux System Programming - UET

This repository contains my solutions and practice exercises for the **Linux System Programming** course at the University of Engineering and Technology (UET), Vietnam National University, Hanoi.

The course provides fundamental knowledge of Linux programming, operating system concepts, process and thread management, file operations, and algorithmic problem solving.

## Course Contents

### Lab 1 – Shell Scripting

Introduction to Linux shell programming and automation.

Topics covered:

* Bash shell basics
* Variables and expressions
* Conditional statements
* Loops and functions
* Script execution and permissions
* File and directory manipulation

### Lab 2 – File I/O Operations

Working with files and directories using Linux system calls.

Topics covered:

* File descriptors
* Opening and closing files
* Reading and writing files
* File permissions
* Directory operations
* Error handling

### Lab 3 – Processes

Understanding process creation and management in Linux.

Topics covered:

* Process lifecycle
* `fork()`
* `exec()` family
* Process synchronization
* Parent-child relationships
* Process termination and waiting

### Lab 4 – Threads

Introduction to concurrent programming using POSIX threads.

Topics covered:

* Thread creation and termination
* Thread attributes
* Thread communication
* Synchronization basics
* Shared resources

### Lab 5 – Multithreaded Programming

Advanced thread programming and synchronization techniques.

Topics covered:

* POSIX Threads (Pthreads)
* Mutexes
* Semaphores
* Condition variables
* Race conditions
* Producer-Consumer problems
* Thread synchronization strategies

### Lab 6 – Dynamic Programming

Algorithmic problem-solving using dynamic programming techniques.

Topics covered:

* Recursive and iterative approaches
* Memoization
* Tabulation
* Optimization problems
* Time and space complexity analysis

## Technologies Used

* Linux (Ubuntu)
* Bash Shell
* C Programming Language
* GCC Compiler
* POSIX APIs
* Pthreads Library

## Requirements

To run and practice the exercises in this repository, you should have access to a Linux environment using one of the following options:

* Install Linux as a dual-boot operating system
* Use CentOS
* Use Windows Subsystem for Linux (WSL)

## Run and Debug a C Program

For every file with the extension `.c` in this repository, you can use the same method to compile and debug it in VS Code or from the terminal.

- `${fileDirname}`: directory containing the current `.c` file
- `${fileBasenameNoExtension}`: current file name without the `.c` extension

Example: if you open `example1.c` in the `Lab3` folder, the debug target is:

- program: `Lab3/example1`
- compile command: `gcc example1.c -g -o example1`

### Compile the current file

```bash
gcc ${fileBasenameNoExtension}.c -g -o ${fileBasenameNoExtension}
```

### Debug configuration example

```json
{
  "name": "Debug current C file",
  "type": "cppdbg",
  "request": "launch",
  "program": "${fileDirname}/${fileBasenameNoExtension}",
  "args": [],
  "cwd": "${fileDirname}",
  "externalConsole": false,
  "MIMode": "gdb",
  "miDebuggerPath": "/usr/bin/gdb"
}
```

This works for all `.c` files in the project: the debugger automatically uses the folder of the opened file and the file name without `.c` as the executable name.

## Repository Structure

```text
.
├── Lab1/
├── Lab2/
├── Lab3/
├── Lab4/
├── Lab5/
├── Lab6/
└── README.md
```

## Learning Objectives

Through these exercises, students will gain practical experience in:

* Linux command-line environments
* Shell scripting and automation
* System-level programming in C
* File and process management
* Concurrent and multithreaded programming
* Algorithm design and optimization

## Disclaimer

This repository is intended for educational purposes only. Solutions are provided as reference implementations and should be used to support learning and understanding of Linux system programming concepts.

## Author 

Nguyen Thanh Vinh
