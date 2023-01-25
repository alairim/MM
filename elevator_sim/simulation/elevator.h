/* Elevator Simulator, version 1 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* Opaque handle type to a simulation */
typedef struct elevator *elevator_h;

/* Bitfield of which buttons are pressed down. */
typedef unsigned button_state;
#define BUTTON_STATE_FLOOR0    0x01
#define BUTTON_STATE_FLOOR1    0x02
#define BUTTON_STATE_FLOOR2    0x04
#define BUTTON_STATE_FLOOR3    0x08
#define BUTTON_STATE_FLOOR4    0x10
#define BUTTON_STATE_EMERGENCY 0x20
#define BUTTON_STATE_START     0x40

/* Bitfield of which lamps should light. */
typedef unsigned lamp_state;
#define LAMP_STATE_FLOOR0    0x01
#define LAMP_STATE_FLOOR1    0x02
#define LAMP_STATE_FLOOR2    0x04
#define LAMP_STATE_FLOOR3    0x08
#define LAMP_STATE_FLOOR4    0x10
#define LAMP_STATE_EMERGENCY 0x40

/* Starts the simulation. Writes a valid handle to *handle_p and returns 0 on
 * success, returns nonzero on failure. */
int start_elevator(elevator_h *handle_p);
/* Stops the simulation */
void stop_elevator(elevator_h);
/* Speeds are between -1 (full speed down) and 1 (full speed up). */
void set_motor_speed(elevator_h, float);
/* Height of the elevator in floors above ground level. Values range between
 * 0.0 (ground floor) and 4.0 (4th floor). */
float get_cart_position(elevator_h);
/* Get the buttons that are currently pressed down */
button_state get_button_state(elevator_h);
/* Opens or closes the doors. */
void set_doors_open(elevator_h, bool);
/* Sets the lamps specified in lamp_state to on, the rest off. */
void set_lamp_state(elevator_h, lamp_state);

#ifdef __cplusplus
}
#endif

#endif // ELEVATOR_H
