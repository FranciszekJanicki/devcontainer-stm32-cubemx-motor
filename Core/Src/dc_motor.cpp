#include "dc_motor.hpp"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include <algorithm>
#include <expected>
#include <utility>

using namespace Motors;
using Direction = DCMotor::Direction;
using Raw = DCMotor::Raw;
using Voltage = DCMotor::Voltage;

namespace Motors {

    void DCMotor::set_voltage(Voltage const voltage) const noexcept
    {
        this->pwm_device.set_compare_voltage(voltage);
    }

    void DCMotor::set_voltage_max() const noexcept
    {
        this->pwm_device.set_compare_max();
    }

    void DCMotor::set_voltage_min() const noexcept
    {
        this->pwm_device.set_compare_min();
    }

    void DCMotor::set_direction(Direction const direction) const noexcept
    {
        if (direction == Direction::SOFT_STOP) {
            HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_RESET);
            HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_RESET);
            this->set_voltage_max();
        } else if (direction == Direction::FAST_STOP) {
            HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_SET);
            this->set_voltage_min();
        } else if (direction == Direction::FORWARD) {
            HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_RESET);
        } else if (direction == Direction::BACKWARD) {
            HAL_GPIO_WritePin(this->gpio, this->pin_left, GPIO_PinState::GPIO_PIN_RESET);
            HAL_GPIO_WritePin(this->gpio, this->pin_right, GPIO_PinState::GPIO_PIN_SET);
        }
    }

    void DCMotor::set_forward() const noexcept
    {
        return this->set_direction(Direction::FORWARD);
    }

    void DCMotor::set_backward() const noexcept
    {
        return this->set_direction(Direction::BACKWARD);
    }

    void DCMotor::set_fast_stop() const noexcept
    {
        return this->set_direction(Direction::FAST_STOP);
    }

    void DCMotor::set_soft_stop() const noexcept
    {
        return this->set_direction(Direction::SOFT_STOP);
    }

}; // namespace Motors
