#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_i2c.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_uart.h"
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <stm32l476xx.h>

namespace Motors::Utility {

    using TIMHandle = TIM_HandleTypeDef*;
    using GPIOHandle = GPIO_TypeDef*;
    using UARTHandle = UART_HandleTypeDef*;
    using I2CBusHandle = I2C_HandleTypeDef*;

    template <typename Value>
    [[nodiscard]] constexpr Value degrees_to_radians(Value const degrees) noexcept
    {
        return degrees * 3.1416F / 180.0F;
    }

    template <typename Value>
    [[nodiscard]] constexpr Value radians_to_degrees(Value const radians) noexcept
    {
        return radians * 180.0F / 3.1416F;
    }

}; // namespace Motors::Utility

#endif // UTILITY_HPP