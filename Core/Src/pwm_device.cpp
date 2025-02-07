#include "pwm_device.hpp"
#include "stm32l4xx_hal.h"
#include "utility.hpp"
#include <algorithm>
#include <utility>

using namespace Motors::Utility;
using std::uint32_t = PWMDevice::std::uint32_t;
using float = PWMDevice::float;

namespace Motors::Utility {

    PWMDevice::PWMDevice(TIMHandle const timer,
                         std::uint32_t const timer_channel,
                         std::uint32_t const min_raw,
                         std::uint32_t const max_raw,
                         float const min_voltage,
                         float const max_voltage) noexcept :
        timer_{timer},
        timer_channel_{timer_channel},
        min_raw_{min_raw},
        max_raw_{max_raw},
        min_voltage_{min_voltage},
        max_voltage_{max_voltage}
    {
        this->initialize();
    }

    PWMDevice::~PWMDevice() noexcept
    {
        this->deinitialize();
    }

    void PWMDevice::set_compare_raw(std::uint32_t const raw) const noexcept
    {
        if (this->initialized_) {
            __HAL_TIM_SetCompare(this->timer_, this->timer_channel_, raw);
        }
    }

    void PWMDevice::set_compare_voltage(float const voltage) const noexcept
    {
        this->set_compare_raw(this->voltage_to_raw(voltage));
    }

    void PWMDevice::set_compare_max() const noexcept
    {
        this->set_compare_raw(this->max_raw_);
    }

    void PWMDevice::set_compare_min() const noexcept
    {
        this->set_compare_raw(this->min_raw_);
    }

    void PWMDevice::set_counter_period(std::uint32_t const counter_period) noexcept
    {
        this->timer_->Init.Period
    }

    void PWMDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_PWM_Start(this->timer_, this->timer_channel_) == HAL_OK) {
                this->initialized_ = true;
            }
        }
    }

    void PWMDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_PWM_Stop(this->timer_, this->timer_channel_) == HAL_OK) {
                this->initialized_ = false;
            }
        }
    }

    std::uint32_t PWMDevice::voltage_to_raw(float const voltage) const noexcept
    {
        return (std::clamp(voltage, this->min_voltage_, this->max_voltage_) - this->min_voltage_) *
               (this->max_raw_ - this->min_raw_) / (this->max_voltage_ - this->min_voltage_);
    }

    float PWMDevice::raw_to_voltage(std::uint32_t const raw) const noexcept
    {
        return std::clamp(raw, this->min_raw_, this->max_raw_) * (this->max_voltage_ - this->min_voltage_) /
                   (this->max_raw_ - this->min_raw_) +
               this->min_voltage_;
    }

}; // namespace Motors::Utility
