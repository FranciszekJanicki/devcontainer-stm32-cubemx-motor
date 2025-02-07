#ifndef PWM_DEVICE_HPP
#define PWM_DEVICE_HPP

#include "stm32l4xx_hal.h"
#include "utility.hpp"
#include <cstdint>

namespace Motors::Utility {

    struct PWMDevice {
    public:
        using TIMHandle = Utility::TIMHandle;

        PWMDevice() noexcept = default;
        PWMDevice(TIMHandle const timer,
                  std::uint32_t const timer_channel,
                  std::uint32_t const min_raw,
                  std::uint32_t const max_raw,
                  float const min_voltage,
                  float const max_voltage) noexcept;

        PWMDevice(PWMDevice const& other) noexcept = delete;
        PWMDevice(PWMDevice&& other) noexcept = default;

        PWMDevice& operator=(PWMDevice const& other) noexcept = delete;
        PWMDevice& operator=(PWMDevice&& other) noexcept = default;

        ~PWMDevice() noexcept;

        void set_compare_raw(std::uint32_t const raw) const noexcept;
        void set_compare_voltage(float const voltage) const noexcept;
        void set_compare_max() const noexcept;
        void set_compare_min() const noexcept;

    private:
        void initialize() noexcept;
        void deinitialize() noexcept;

        std::uint32_t voltage_to_raw(float const voltage) const noexcept;
        float raw_to_voltage(std::uint32_t const raw) const noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};
        std::uint32_t timer_channel_{};

        std::uint32_t min_raw_{};
        std::uint32_t max_raw_{};
        float min_voltage_{};
        float max_voltage_{};
    };

}; // namespace Motors::Utility

#endif // PWM_DEVICE_HPP