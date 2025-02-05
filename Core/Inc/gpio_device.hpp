#ifndef GPIO_DEVICE_HPP
#define GPIO_DEVICE_HPP

#include "gpio_device.hpp"
#include "stm32l4xx_hal_gpio.h"
#include "utility.hpp"

namespace Motors::Utility {

    struct GPIODevice {
        enum struct State {
            SET,
            RESET,
        };

        using Pin = std::uint16_t;

        void write_pin(Pin const pin,
                       State const state) noexcept {HAL_GPIO_WritePin(this -> gpio, 1U << pin | 1 << 2, )}

        GPIOHandle gpio {
            nullptr
        };
    };

}; // namespace Motors::Utility

#endif // GPIO_DEVICE_HPP