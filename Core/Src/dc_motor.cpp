#include "dc_motor.hpp"
#include "main.h"
#include "pid.hpp"
#include <cstdio>
#include <functional>
#include <memory>
#include <utility>
#include <variant>

namespace Motors {

    void DCMotor::operator()(float const input_speed, float const sampling_time) noexcept
    {
        this->set_speed(this->get_control_speed(this->get_error_speed(input_speed, sampling_time), sampling_time));
    }

    void DCMotor::set_speed(float const control_speed) const noexcept
    {
        this->set_direction(control_speed);
        this->set_voltage(control_speed);
    }

    void DCMotor::set_direction(float const control_speed) const noexcept
    {
        this->motor.set_direction(std::invoke(this->speed_to_direction, control_speed));
    }

    void DCMotor::set_voltage(float const control_speed) const noexcept
    {
        this->motor.set_voltage(std::invoke(this->speed_to_voltage, std::abs(control_speed)));
    }

    float DCMotor::get_measured_speed(float const sampling_time) noexcept
    {
        return this->encoder.get_speed_degrees(sampling_time).value_or(0.0F);
    }

    float DCMotor::get_control_speed(float const error_speed, float const sampling_time) noexcept
    {
        return std::invoke(this->regulator, error_speed, sampling_time);
    }

    float DCMotor::get_error_speed(float const input_speed, float const sampling_time) noexcept
    {
        return input_speed - this->get_measured_speed(sampling_time);
    }

}; // namespace Motors
