#include "h_bridge.hpp"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_tim.h"
#include <algorithm>
#include <expected>
#include <utility>

using namespace Motors;
using Direction = HBridge::Direction;
using Raw = HBridge::Raw;
using Voltage = HBridge::Voltage;

namespace Motors {

    void HBridge::set_voltage(Voltage const voltage) const noexcept
    {
        this->pwm_device.set_compare_voltage(voltage);
    }

    void HBridge::set_max_voltage() const noexcept
    {
        this->pwm_device.set_compare_max();
    }

    void HBridge::set_min_voltage() const noexcept
    {
        this->pwm_device.set_compare_min();
    }

    void HBridge::set_direction(Direction const direction) const noexcept
    {
        switch (direction) {
            case Direction::SOFT_STOP:
                this->set_soft_stop();
                break;
            case Direction::FAST_STOP:
                this->set_fast_stop();
                break;
            case Direction::FORWARD:
                this->set_forward();
                break;
            case Direction::BACKWARD:
                this->set_backward();
                break;
        }
    }

    void HBridge::set_forward_direction() const noexcept
    {
        HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_RESET);
        this->set_max_voltage();
    }

    void HBridge::set_backward_direction() const noexcept
    {
        HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_SET);
        HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_SET);
        this->set_min_voltage();
    }

    void HBridge::set_fast_stop_direction() const noexcept
    {
        HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_SET);
        HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_RESET);
    }

    void HBridge::set_soft_stop_direction() const noexcept
    {
        HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_SET);
    }

}; // namespace Motors
