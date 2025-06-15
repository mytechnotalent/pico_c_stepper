/**
 * @file main.c
 * @brief Main entry point for LED blinking and stepper motor control application
 * @version 1.0
 * @date 2025-06-15
 * @author Kevin Thomas
 *
 * This is the main application entry point for a Raspberry Pi Pico project that
 * combines LED blinking with 4-channel stepper motor control using ULN2003 drivers.
 * The application demonstrates GPIO control, timing functions, and modular code
 * organization suitable for embedded C development.
 *
 * @copyright Copyright (c) 2025 Kevin Thomas
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "src/run.h"

/**
 * @brief Main entry point of the application
 *
 * Initializes the system and starts the main application loop by calling
 * the run function. This function serves as a minimal entry point that
 * delegates the actual application logic to the run module.
 *
 * @return int Program exit status (never reached in normal operation)
 */
int main(void)
{
    // Initialize standard I/O
    stdio_init_all();

    // Start the main application
    run();

    return 0;
}
