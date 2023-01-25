#include "elevator.h"

#include <mutex>
#include <atomic>

#ifndef ELEVATOR_OUTPUT_H
#define ELEVATOR_OUTPUT_H

struct elevator_output {
    elevator_output() {
        std::atomic_init(&simulation_stopped, false);
    }
    /* Not guarded by mutex, unlike rest of members */
    std::atomic_bool simulation_stopped;

    std::mutex mutex;
    button_state buttons = 0;
    float cart_position = 0;
    // float cart_velocity;
};

#endif // ELEVATOR_OUTPUT_H
