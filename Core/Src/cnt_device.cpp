#include "cnt_device.hpp"
#include "stm32l4xx_hal.h"
#include <optional>
#include <utility>

using namespace Motors::Utility;
using Count = CNTDevice::Count;
using OptionalCount = CNTDevice::OptionalCount;

namespace Motors::Utility {

    CNTDevice::CNTDevice(TimerHandle const timer, Count const counter_period) noexcept :
        timer_{timer}, counter_period_{counter_period}
    {
        this->initialize();
    }

    CNTDevice::~CNTDevice() noexcept
    {
        this->deinitialize();
    }

    OptionalCount CNTDevice::get_count() const noexcept
    {
        if (!this->initialized_) {
            return OptionalCount{std::nullopt};
        }
        this->count_ = this->get_current_count() % this->counter_period_;
        return OptionalCount{this->count_};
    }

    OptionalCount CNTDevice::get_count_difference() const noexcept
    {
        auto prev_count{this->count_};
        return this->get_count().transform([prev_count](Count const count) { return count - prev_count; });
    }

    void CNTDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Start(this->timer_, TIM_CHANNEL_ALL) == HAL_OK) {
                this->initialized_ = true;
            }
        }
    }

    void CNTDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Stop(this->timer_, TIM_CHANNEL_ALL) == HAL_OK) {
                this->initialized_ = false;
            }
        }
    }

    Count CNTDevice::get_current_count() const noexcept
    {
        return static_cast<Count>(__HAL_TIM_GetCounter(this->timer_));
    }

}; // namespace Motors::Utility