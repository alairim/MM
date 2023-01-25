#include "simulation.h"

#include <algorithm>
#include <cmath>
#include <cassert>

Simulation::Simulation() {
}

Simulation::~Simulation() {
}

void Simulation::setDoorsOpen(bool open) {
    doors_open = open;
}

void Simulation::setMotorSpeed(float speed) {
    motor_speed = speed;
}

void Simulation::setErrorInjection(bool on) {
    error_inject = on;
}

float Simulation::get_tick_length() {
    return 0.00001;
}

float Simulation::get_cart_position() const {
    return position;
}

float Simulation::get_position_signal() const {
    if (!error_inject)
        return position;
    else {
        auto rng = [](int in) { return ((in*5754853343) >> 20) & 0xff; };
        int seconds = (int)t;
        float basepos = rng(seconds) / 255.f * 4.3f;
        float extra = rng((int)(t * 10)) < 30 ? -0.3 : 0;
        return basepos + extra;
    }
}

bool Simulation::get_doors_open() const {
    return doors_open;
}

bool Simulation::has_error() const {
    return error;
}

const std::string &Simulation::get_error_message() const {
    return error_message;
}

namespace {
float clamp(float val, float min, float max) {
    assert(min <= max);
    if (val < min) return min;
    if (val > max) return max;
    return val;
}
}

void Simulation::tick() {
    float max_accel = (2 - fabs(velocity)) * get_tick_length();
    velocity += clamp(motor_speed - velocity, -max_accel, max_accel);
    position += velocity * get_tick_length();
    t += get_tick_length();

    float cart_position = get_cart_position();
    /* Check for errors */
    if (!error && (cart_position <= -0.5 || cart_position >= 4.5f)) {
        error = true;
        error_message = std::string("Cart too far ") + (cart_position < 0 ? "down" : "up");
    }
    if (!error && doors_open &&
            (std::abs(std::remainderf(cart_position, 1.0f)) > 0.1f
             || fabs(velocity) > 0.05f)) {
        error = true;
        error_message = "Doors open while cart was moving";
    }

}
