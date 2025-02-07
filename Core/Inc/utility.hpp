#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_i2c.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_uart.h"
#include <concepts>
#include <cstdint>

namespace Motors::Utility {

    using TIMHandle = TIM_HandleTypeDef*;
    using GPIOHandle = GPIO_TypeDef*;
    using UARTHandle = UART_HandleTypeDef*;
    using I2CBusHandle = I2C_HandleTypeDef*;

    template <typename T>
    [[nodiscard]] T degrees_to_radians(T const degrees) noexcept
    {
        return degrees * 3.1416F / 180.0F;
    }

    template <typename T>
    [[nodiscard]] T radians_to_degrees(T const radians) noexcept
    {
        return radians * 180.0F / 3.1416F;
    }

    template <typename T>
    [[nodiscard]] T differentiate(T const value,
                                  T const prev_value,
                                  T const sampling_time,
                                  T const prev_derivative,
                                  T const time_constant) noexcept
    {
        if (time_constant + sampling_time == static_cast<T>(0.0F)) {
            return static_cast<T>(0.0F);
        }
        return (value - prev_value + prev_derivative * time_constant) / (time_constant + sampling_time);
    }

    template <typename T>
    [[nodiscard]] T differentiate(T const value, T const prev_value, T const sampling_time) noexcept
    {
        if (sampling_time == static_cast<T>(0.0F)) {
            return static_cast<T>(0.0F);
        }
        return (value - prev_value) / sampling_time;
    }

    template <typename T>
    [[nodiscard]] T integrate(T const value, T const prev_value, T const sampling_time) noexcept
    {
        return (value + prev_value) * static_cast<T>(0.5F) * sampling_time;
    }

}; // namespace Motors::Utility

#endif // UTILITY_HPP