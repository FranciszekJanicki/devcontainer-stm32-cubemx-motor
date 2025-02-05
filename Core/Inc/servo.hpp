#ifndef SERVO_HPP
#define SERVO_HPP

#include "pwm_device.hpp"
#include "stm32l4xx_hal.h"
#include "utility.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <utility>

namespace Motors {

    struct Servo {
    public:
        using Angle = float;
        using Voltage = Utility::PWMDevice::Voltage;
        using AngleToVoltage = Voltage (*)(Angle) noexcept;

        void set_angle(Angle const angle) const noexcept;
        void set_angle_max() const noexcept;
        void set_angle_min() const noexcept;

        template <typename... Angles>
        void run_sequence(Angles const... angles) noexcept
        {
            for (auto const angle : std::array<Angle, sizeof...(angles)>{angles...}) {
                this->set_angle(angle);
                HAL_Delay(50);
            }
        }

        AngleToVoltage angle_to_voltage{};

        Utility::PWMDevice pwm_device{};
    };

}; // namespace Motors

#endif // SERVO_HPP