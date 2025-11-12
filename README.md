# STM32 BH1750 Driver Library and Demo

This repository serves two purposes:

1. **Providing a robust, reusable BH1750 driver library** for STM32 microcontrollers.

2. **Demonstrating its usage** in an application that logs data via UART.

The core BH1750 logic is abstracted into a custom library to ensure clean separation from the main application code.

## Project Structure and Driver Location

The core driver files are located in the `Libraries` folder, making them modular and easy to include in other projects.

| **Location** | **File** | **Description** |
| :--- | :--- | :--- |
| `Libraries/Inc/` | `bh1750.h` | **The Driver Header File.** Defines the `bh1750_handle_t` struct, status enumerations, and the public API for the driver. |
| `Libraries/Src/` | `bh1750.c` | **The Core Driver Implementation.** Contains the logic for the I2C based communication driver. |
| `Core/Src/` | `main.c` | **Demonstration Application.** Initializes peripherals, calls the BH1750 driver functions, includes error handling, and prints continuous readings via UART. |

## Getting Started

### Hardware Requirements

* **Microcontroller:** STM32F411RE Nucleo Board (or any compatible STM32F4 microcontroller)
* **Sensor:** BH1750 Ambient Light Sensor
* **Connections:** See **Pinout Configuration** below.

### Software Requirements

* STM32CubeIDE (or compatible ARM-based IDE)
* GNU ARM Embedded Toolchain

### I2C Configuration
Configure one of the I2C modules available in STM32CubeIDE IOC Pinout & Configuration tab. This code uses I2C1 with PB8 & PB9 pins.

### Pinout Configuration

The demo application is configured to use the following pins on the STM32:

| **BH1750 Pin** | **STM32 Pin** |
| :--- | :--- |
| **SCL** | D15/PB8 |
| **SDA** | D14/PB9 |
| **ADDR** | Any GND Pin |
| **VCC** | Any 3V Pin |
| **GND** | Any GND Pin |

## Driver API

The following are the primary functions provided by the BH1750 driver library:

### `bh1750_init`

Initializes the sensor handle, linking it to the specified hardware peripherals (I2C).

```c
bh1750_status bh1750_init(bh1750_handle_t *handle, I2C_HandleTypeDef *hi2c, uint8_t i2c_addr);
```

### `bh1750_read_lux`

Executes a complete reading cycle by reading the raw data values from the sensor and converting it to lux values.

```c
void bh1750_read_lux(bh1750_handle_t *handle);
```

## Compilation and Running

### BH1750 Driver
* Clone this repository locally.
* Copy the `Libraries` folder into your workspace.
* Add the `Libraries\Inc` folder path into the project (`Properties -> C/C++ General -> Paths and Symbols -> Includes -> Add`).
* Add the `Libraries\Src` those as source Locations (`Properties -> C/C++ General -> Paths and Symbols -> Source Locations -> Add Folder`).

### Complete Project
* Clone this repository locally.
* Import the project into `STM32CubeIDE using File > Import... > General > Existing Projects into Workspace`.
* Ensure your target hardware configuration (`STM32F411RE`) matches your board.
* Build the project.
* Flash the generated `.elf` file onto your STM32 using an ST-Link/J-Link debugger.
* Open a serial terminal configured to `115200` Baud to view the live temperature and humidity data.
