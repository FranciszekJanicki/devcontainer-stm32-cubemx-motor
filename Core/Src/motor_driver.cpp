#include "motor_driver.hpp"
#include "main.h"
#include "pid.hpp"
#include <cstdio>
#include <functional>
#include <memory>
#include <utility>
#include <variant>

using namespace Motors;
using Value = MotorDriver::Value;
using Direction = MotorDriver::Direction;
using Regulator = MotorDriver::Regulator;

namespace Motors {

    void MotorDriver::operator()(Value const input_speed, Value const dt) noexcept
    {
        this->set_speed(this->get_control_speed(this->get_error_speed(input_speed, dt), dt));
    }

    void MotorDriver::set_speed(Value const control_speed) const noexcept
    {
        this->set_direction(control_speed);
        this->set_voltage(control_speed);
    }

    void MotorDriver::set_direction(Value const control_speed) const noexcept
    {
        this->motor.set_direction(std::invoke(this->speed_to_direction, control_speed));
    }

    void MotorDriver::set_voltage(Value const control_speed) const noexcept
    {
        this->motor.set_voltage(std::invoke(this->speed_to_voltage, std::abs(control_speed)));
    }

    Value MotorDriver::get_measured_speed(Value const dt) noexcept
    {
        return this->encoder.get_speed_degrees(dt).value_or(0.0F);
    }

    Value MotorDriver::get_control_speed(Value const error_speed, Value const dt) noexcept
    {
        return std::invoke(this->regulator, error_speed, dt);
    }

    Value MotorDriver::get_error_speed(Value const input_speed, Value const dt) noexcept
    {
        return input_speed - this->get_measured_speed(dt);
    }

}; // namespace Motors
