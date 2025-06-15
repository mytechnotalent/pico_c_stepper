/**
 * @file run.c
 * @brief LED control and stepper motor application implementation
 * @version 1.0
 * @date 2025-06-15
 * @author Kevin Thomas
 *
 * This source file implements the main application logic for controlling
 * both LED blinking and stepper motor operations on the Raspberry Pi Pico.
 * Provides a unified interface for the combined functionality.
 *
 * @copyright Copyright (c) 2025 Kevin Thomas
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "run.h"

// Constants for LED configuration
#define LED_BLINK_DELAY_MS 500

// Constants for stepper motor configuration
#define NUM_STEPPERS 4
#define STEPPER_DELAY_MS 3
#define STEPPER_DEMO_ANGLE 45.0f
#define STEPPER_PAUSE_MS 500
#define STEPPER_CYCLE_INTERVAL 5

// GPIO pin assignments for stepper motors
static const uint stepper_pins[NUM_STEPPERS][4] = {
    {2, 3, 6, 7},     // Stepper Motor 1
    {10, 11, 14, 15}, // Stepper Motor 2
    {18, 19, 20, 21}, // Stepper Motor 3
    {22, 26, 27, 28}  // Stepper Motor 4
};

void led_blink_cycle(uint led_pin)
{
    gpio_put(led_pin, 1);
    printf("LED ON\n");
    sleep_ms(LED_BLINK_DELAY_MS);

    gpio_put(led_pin, 0);
    printf("LED OFF\n");
    sleep_ms(LED_BLINK_DELAY_MS);
}

void control_steppers(stepper_motor_t *steppers, uint num_steppers)
{
    // Create array of pointers for bulk operations
    stepper_motor_t *stepper_ptrs[NUM_STEPPERS];
    for (uint i = 0; i < num_steppers; i++)
    {
        stepper_ptrs[i] = &steppers[i];
    }

    // Use the bulk demo sequence function
    stepper_demo_sequence(stepper_ptrs, num_steppers, STEPPER_DEMO_ANGLE, STEPPER_PAUSE_MS);
}

/**
 * @brief Initialize all stepper motors with predefined GPIO pins
 *
 * @param steppers Array of stepper motor structures to initialize
 * @param num_steppers Number of steppers to initialize
 * @return true if all motors initialized successfully, false otherwise
 */
static bool init_all_steppers(stepper_motor_t *steppers, uint num_steppers)
{
    if (num_steppers > NUM_STEPPERS)
    {
        printf("Error: Requested %d steppers, but only %d configurations available\n",
               num_steppers, NUM_STEPPERS);
        return false;
    }

    for (uint i = 0; i < num_steppers; i++)
    {
        if (!stepper_init(&steppers[i],
                          stepper_pins[i][0], stepper_pins[i][1],
                          stepper_pins[i][2], stepper_pins[i][3],
                          STEPPER_DELAY_MS))
        {
            printf("Failed to initialize stepper motor %d\n", i + 1);
            return false;
        }
        printf("Stepper motor %d initialized on pins %d,%d,%d,%d\n",
               i + 1, stepper_pins[i][0], stepper_pins[i][1],
               stepper_pins[i][2], stepper_pins[i][3]);
    }

    return true;
}

void run(void)
{
    // Initialize LED pin configuration
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Initialize 4 stepper motors with GPIO pins avoiding UART pins
    stepper_motor_t steppers[NUM_STEPPERS];

    if (!init_all_steppers(steppers, NUM_STEPPERS))
    {
        printf("Stepper motor initialization failed. Exiting...\n");
        return;
    }

    printf("All stepper motors initialized successfully!\n");
    printf("Starting LED blink and stepper motor control loop...\n");

    uint cycle_count = 0;

    // Main application loop - runs indefinitely
    while (true)
    {
        led_blink_cycle(LED_PIN);

        // Run stepper motors every STEPPER_CYCLE_INTERVAL LED blink cycles to avoid overwhelming output
        if (cycle_count % STEPPER_CYCLE_INTERVAL == 0)
        {
            control_steppers(steppers, NUM_STEPPERS);
        }

        cycle_count++;
    }
}
