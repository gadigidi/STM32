# Project Overview #

This repository is a **hands-on STM32 firmware learning project**.

The goal is to gain **practical experience** with STM32 microcontrollers through direct work
with peripherals and **register-level programming**, focusing on learning by doing rather than
production-ready code.

All development and testing are performed on **real STM32 hardware**, using physical wiring
and external peripherals.

The project is built **incrementally**, with each stage focusing on a specific peripheral or concept.
It is **continuously updated** as new topics are explored and understanding evolves.
Over time, these building blocks are combined into a more complete system.

This repository represents an **ongoing learning process**, not a final product.

# Project Structure #

- Src        -> Source files (.c)
- Inc        -> Header files (.h)
- Documents  -> Media and documentation

# Status #

In Progress

# Implemented #

- **GPIO driver**  
  Basic GPIO configuration for input and output control, focusing on pin modes, pull-up/down settings, and direct register access.

- **ADC driver**  
  Analog-to-digital conversion configured for single-channel sampling to practice resolution, sample time selection, and raw data acquisition.

- **Joystick driver**  
  Analog joystick interfaced via ADC to experiment with multi-axis input reading and practical signal sampling behavior.

- **4-digit 7-segment display driver**  
  Multiplexed 7-segment display driven directly from GPIO pins to practice low-level output control and timing.

- **TIMER2 driver**  
  TIM2 configured as a periodic time base to practice prescaler and auto-reload setup, interrupts, and time-based event handling.
  
