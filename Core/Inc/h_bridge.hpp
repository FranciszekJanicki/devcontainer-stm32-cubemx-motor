#ifndef H_BRIDGE_HPP
#define H_BRIDGE_HPP

#include "pwm_device.hpp"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "utility.hpp"
#include <cstdint>

namespace Motors {

    struct HBridge {
    public:
        enum struct Direction : std::uint8_t {
            FORWARD,
            BACKWARD,
            FAST_STOP,
            SOFT_STOP,
        };

        using PWMDevice = Utility::PWMDevice;
        using GPIOHandle = Utility::GPIOHandle;

        void set_voltage(float const voltage) const noexcept;
        void set_max_voltage() const noexcept;
        void set_min_voltage() const noexcept;

        void set_direction(Direction const direction) const noexcept;
        void set_forward_direction() const noexcept;
        void set_backward_direction() const noexcept;
        void set_soft_stop_direction() const noexcept;
        void set_fast_stop_direction() const noexcept;

        Utility::PWMDevice pwm_device{};

        Utility::GPIOHandle gpio{nullptr};
        std::uint16_t pin_left{};
        std::uint16_t pin_right{};
    };

}; // namespace Motors

#endif // H_BRIDGE_HPP