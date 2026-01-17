# Real-Time Multicore System on Raspberry Pi (Bare-Metal ARM)

## Project Overview

This project consists of a series of advanced system programming labs (TP6, TP7, TP8) carried out on a **Raspberry Pi (ARMv8, bare-metal)**.  
The goal was to design, implement, and execute a **real-time multicore system** without any operating system, directly on the hardware.

The project covers:
- bare-metal boot and execution,
- multicore synchronization,
- real-time task scheduling,
- deployment and execution on a physical Raspberry Pi.

**This project was developed in collaboration with a fellow student Walid Perot.**

---

## Global Objectives

- Understand ARMv8 bare-metal execution
- Implement multicore synchronization mechanisms
- Design and integrate a real-time scheduler
- Deploy and run a custom runtime on Raspberry Pi hardware
- Bridge the gap between simulation and real embedded execution

---

Each TP builds on the previous one and represents a new level of system complexity.

---

## TP6 — Bare-Metal Runtime & Multicore Execution

**Objective:**  
Develop a minimal bare-metal runtime for ARMv8 and execute concurrent code on multiple cores of a Raspberry Pi.

**Key Achievements:**
- Custom boot sequence (EL2 → EL1)
- Memory initialization and MMU setup
- Multicore startup and synchronization
- UART-based debugging and logging
- Execution of concurrent tasks on multiple cores

**Skills demonstrated:**  
Bare-metal programming, ARMv8 architecture, low-level boot process, hardware interaction.

---

## TP7 — Real-Time Task Scheduling

**Objective:**  
Design and integrate a **real-time scheduler** to manage multiple tasks across CPU cores.

**Key Achievements:**
- Modeling a scheduler using **Heptagon**
- Simulation of scheduling policies on PC
- Generation of C code from the formal model
- Integration of the scheduler into the bare-metal runtime
- Execution of scheduled tasks on Raspberry Pi cores

**Skills demonstrated:**  
Real-time systems, scheduling algorithms, model-based design, multicore coordination.

---

## TP8 — Bi-Core Real-Time Execution on Raspberry Pi

**Objective:**  
Deploy a **bi-core real-time scheduler** on actual Raspberry Pi hardware.

**Key Achievements:**
- Adaptation of the scheduler for a bi-core ARM architecture
- Synchronization between two cores using atomic primitives
- Real-time task execution and observation on hardware
- Validation of scheduling behavior compared to simulation

**Skills demonstrated:**  
Multicore synchronization, real-time embedded systems, hardware/software integration.

---

## Technologies & Tools

- **Architecture:** ARMv8 (AArch64)
- **Platform:** Raspberry Pi (bare-metal)
- **Languages:** C, ARM Assembly
- **Modeling:** Heptagon
- **Toolchain:** `aarch64-none-elf-gcc`
- **Debugging:** UART serial communication

---

## Key Takeaways

This project provided hands-on experience with:
- low-level system programming,
- real-time scheduling,
- multicore embedded execution,
- and deploying complex software directly on hardware without an OS.

It reflects a complete workflow from **formal modeling → simulation → hardware execution**.

---

## Authors

- **Meyssem**  
- Project completed **in duo with a fellow student** as part of an advanced systems course.


