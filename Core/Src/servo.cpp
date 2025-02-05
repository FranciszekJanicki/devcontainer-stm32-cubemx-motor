#include "servo.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <utility>

using namespace Motors;
using Angle = Servo::Angle;

namespace Motors {

    void Servo::set_angle(Angle const angle) const noexcept
    {
        this->pwm_device.set_compare_voltage(std::invoke(this->angle_to_voltage, angle));
    }

    void Servo::set_angle_max() const noexcept
    {
        this->pwm_device.set_compare_max();
    }

    void Servo::set_angle_min() const noexcept
    {
        this->pwm_device.set_compare_min();
    }

}; // namespace Motors