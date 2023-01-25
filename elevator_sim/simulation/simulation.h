#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

class Simulation
{
public:
    Simulation();
    ~Simulation();
    void setDoorsOpen(bool open);
    void setMotorSpeed(float speed);
    void setErrorInjection(bool on);
    static float get_tick_length();
    void tick();
    float get_cart_position() const;
    float get_position_signal() const;
    bool get_doors_open() const;
    bool has_error() const;
    const std::string &get_error_message() const;
private:
    // float cart_position = 0;
    // float motor_speed = 0;
    bool doors_open = false;
    bool error = false;
    bool error_inject = false;
    std::string error_message;

    float t = 0;
    float position = 0;
    float velocity = 0;
    float motor_speed = 0;
};

#endif // SIMULATION_H
