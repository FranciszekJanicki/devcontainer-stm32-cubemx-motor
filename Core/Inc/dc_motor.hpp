#ifndef DC_MOTOR_HPP
#define DC_MOTOR_HPP

#include "pwm_device.hpp"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "utility.hpp"
#include <cstdint>

namespace Motors {

    struct DCMotor {
    public:
        enum struct Direction {
            FORWARD,
            BACKWARD,
            FAST_STOP,
            SOFT_STOP,
        };

        using Raw = Utility::PWMDevice::Raw;
        using Voltage = Utility::PWMDevice::Voltage;

        void set_voltage(Voltage const voltage) const noexcept;
        void set_voltage_max() const noexcept;
        void set_voltage_min() const noexcept;

        void set_direction(Direction const direction) const noexcept;
        void set_forward() const noexcept;
        void set_backward() const noexcept;
        void set_soft_stop() const noexcept;
        void set_fast_stop() const noexcept;

        Utility::PWMDevice pwm_device{};

        Utility::GPIOHandle gpio{nullptr};
        std::uint16_t pin_left{};
        std::uint16_t pin_right{};
    };

}; // namespace Motors

#endif // DC_MOTOR_HPP