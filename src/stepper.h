/**
 * @file stepper.h
 * @brief ULN2003 28BYJ-48 4-Phase Stepper Motor Driver Interface
 * @version 1.0
 * @date 2025-06-15
 * @author Kevin Thomas
 *
 * This header file provides a comprehensive interface for controlling ULN2003
 * 28BYJ-48 4-phase stepper motors with the Raspberry Pi Pico. The driver
 * supports multiple stepper motors with configurable GPIO pins and provides
 * both step-based and degree-based rotation control.
 *
 * The ULN2003 driver board requires 4 GPIO pins per motor for 4-phase control
 * and operates optimally with 5V motor power supply. The implementation uses
 * half-stepping (8-step sequence) for smooth operation and maximum torque.
 *
 * Hardware Requirements:
 * - ULN2003 stepper motor driver boards
 * - 28BYJ-48 stepper motors (5V, 4-phase)
 * - 5V power supply (VBUS from USB recommended)
 * - 4 GPIO pins per motor for control signals
 *
 * Technical Specifications:
 * - Steps per revolution: 2048 (32 steps × 64:1 gear ratio)
 * - Voltage: 5V (motor), 3.3V (logic)
 * - Current per motor: ~160mA
 * - Control method: 4-phase half-stepping
 * - Step resolution: 0.176° per step
 *
 * @copyright Copyright (c) 2025 Kevin Thomas
 */

#ifndef STEPPER_H
#define STEPPER_H

#include "pico/stdlib.h"

/**
 * @brief Maximum number of stepper motors supported
 */
#define MAX_STEPPERS 4

/**
 * @brief Number of steps per full revolution for 28BYJ-48 motor
 * 28BYJ-48 has 32 steps per revolution with internal gear ratio of 64:1
 * Total steps = 32 * 64 = 2048 steps per full revolution
 */
#define STEPS_PER_REVOLUTION 2048

/**
 * @brief Number of phases in the stepper motor
 */
#define STEPPER_PHASES 4

/**
 * @brief Stepper motor rotation direction
 */
typedef enum
{
    STEPPER_CW = 0, /*!< Clockwise rotation */
    STEPPER_CCW = 1 /*!< Counter-clockwise rotation */
} stepper_direction_t;

/**
 * @brief Stepper motor configuration structure
 */
typedef struct
{
    uint pin1;        /*!< GPIO pin for phase 1 (IN1) */
    uint pin2;        /*!< GPIO pin for phase 2 (IN2) */
    uint pin3;        /*!< GPIO pin for phase 3 (IN3) */
    uint pin4;        /*!< GPIO pin for phase 4 (IN4) */
    uint step_delay;  /*!< Delay between steps in milliseconds */
    int current_step; /*!< Current step position (0-7) */
    bool enabled;     /*!< Motor enable state */
} stepper_motor_t;

/**
 * @brief Initialize a stepper motor
 *
 * This function initializes a stepper motor by configuring the GPIO pins
 * as outputs and setting up the initial state.
 *
 * @param motor Pointer to the stepper motor structure
 * @param pin1 GPIO pin for phase 1 (IN1)
 * @param pin2 GPIO pin for phase 2 (IN2)
 * @param pin3 GPIO pin for phase 3 (IN3)
 * @param pin4 GPIO pin for phase 4 (IN4)
 * @param step_delay Delay between steps in milliseconds (recommended: 2-10ms)
 *
 * @return true if initialization successful, false otherwise
 */
bool stepper_init(stepper_motor_t *motor, uint pin1, uint pin2, uint pin3, uint pin4, uint step_delay);

/**
 * @brief Move stepper motor by specified number of steps
 *
 * This function moves the stepper motor by the specified number of steps
 * in the given direction using 4-phase stepping sequence.
 *
 * @param motor Pointer to the stepper motor structure
 * @param steps Number of steps to move
 * @param direction Direction of rotation (STEPPER_CW or STEPPER_CCW)
 */
void stepper_move_steps(stepper_motor_t *motor, uint steps, stepper_direction_t direction);

/**
 * @brief Rotate stepper motor by specified degrees
 *
 * This function rotates the stepper motor by the specified number of degrees.
 * Uses the STEPS_PER_REVOLUTION constant to calculate the required steps.
 *
 * @param motor Pointer to the stepper motor structure
 * @param degrees Degrees to rotate (can be fractional)
 * @param direction Direction of rotation (STEPPER_CW or STEPPER_CCW)
 */
void stepper_rotate_degrees(stepper_motor_t *motor, float degrees, stepper_direction_t direction);

/**
 * @brief Disable stepper motor (turn off all phases)
 *
 * This function turns off all phases of the stepper motor to reduce
 * power consumption and heat generation.
 *
 * @param motor Pointer to the stepper motor structure
 */
void stepper_disable(stepper_motor_t *motor);

/**
 * @brief Enable stepper motor
 *
 * This function enables the stepper motor for operation.
 *
 * @param motor Pointer to the stepper motor structure
 */
void stepper_enable(stepper_motor_t *motor);

/**
 * @brief Set stepper motor speed
 *
 * This function sets the delay between steps, which controls the motor speed.
 * Lower delay = faster speed, but too low may cause the motor to stall.
 *
 * @param motor Pointer to the stepper motor structure
 * @param step_delay Delay between steps in milliseconds (recommended: 2-10ms)
 */
void stepper_set_speed(stepper_motor_t *motor, uint step_delay);

/**
 * @brief Get current step position
 *
 * This function returns the current step position in the stepping sequence.
 *
 * @param motor Pointer to the stepper motor structure
 * @return Current step position (0-7)
 */
int stepper_get_position(stepper_motor_t *motor);

/**
 * @brief Rotate multiple stepper motors simultaneously by degrees
 *
 * This function rotates multiple stepper motors by the same number of degrees
 * in the same direction. All motors rotate simultaneously rather than sequentially.
 *
 * @param motors Array of pointers to stepper motor structures
 * @param num_motors Number of motors in the array
 * @param degrees Degrees to rotate (can be fractional)
 * @param direction Direction of rotation (STEPPER_CW or STEPPER_CCW)
 */
void stepper_rotate_multiple_degrees(stepper_motor_t *motors[], uint num_motors,
                                     float degrees, stepper_direction_t direction);

/**
 * @brief Execute a demonstration sequence on multiple stepper motors
 *
 * This function performs a standard demonstration sequence on multiple motors:
 * - Rotate all motors clockwise by specified degrees
 * - Wait for specified delay
 * - Rotate all motors counter-clockwise by specified degrees
 * - Wait for specified delay
 *
 * @param motors Array of pointers to stepper motor structures
 * @param num_motors Number of motors in the array
 * @param degrees Degrees to rotate in each direction
 * @param pause_ms Delay between operations in milliseconds
 */
void stepper_demo_sequence(stepper_motor_t *motors[], uint num_motors,
                           float degrees, uint pause_ms);

#endif /* STEPPER_H */
