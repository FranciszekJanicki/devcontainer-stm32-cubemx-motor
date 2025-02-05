#ifndef PWM_DEVICE_HPP
#define PWM_DEVICE_HPP

#include "stm32l4xx_hal.h"
#include "utility.hpp"
#include <cstdint>

namespace Motors::Utility {

    struct PWMDevice {
    public:
        using Voltage = float;
        using Raw = std::uint32_t;

        PWMDevice() noexcept = default;
        PWMDevice(TIMHandle const timer,
                  std::uint32_t const timer_channel,
                  Raw const min_raw,
                  Raw const max_raw,
                  Voltage const min_voltage,
                  Voltage const max_voltage) noexcept;

        PWMDevice(PWMDevice const& other) noexcept = delete;
        PWMDevice(PWMDevice&& other) noexcept = default;

        PWMDevice& operator=(PWMDevice const& other) noexcept = delete;
        PWMDevice& operator=(PWMDevice&& other) noexcept = default;

        ~PWMDevice() noexcept;

        void set_compare_raw(Raw const raw) const noexcept;
        void set_compare_voltage(Voltage const voltage) const noexcept;
        void set_compare_max() const noexcept;
        void set_compare_min() const noexcept;

    private:
        void initialize() noexcept;
        void deinitialize() noexcept;

        Raw voltage_to_raw(Voltage const voltage) const noexcept;
        Voltage raw_to_voltage(Raw const raw) const noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};
        std::uint32_t timer_channel_{};

        Raw min_raw_{};
        Raw max_raw_{};
        Voltage min_voltage_{};
        Voltage max_voltage_{};
    };

}; // namespace Motors::Utility

#endif // PWM_DEVICE_HPP