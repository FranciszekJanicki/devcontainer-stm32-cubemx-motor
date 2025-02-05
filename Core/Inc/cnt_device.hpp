#ifndef CNT_DEVICE_HPP
#define CNT_DEVICE_HPP

#include "stm32l4xx_hal_tim.h"
#include "utility.hpp"
#include <cstdint>
#include <functional>
#include <optional>

namespace Motors::Utility {

    struct CNTDevice {
    public:
        using Count = std::uint32_t;
        using OptionalCount = std::optional<Count>;

        CNTDevice() noexcept = default;
        CNTDevice(TIMHandle const timer, Count const counter_period) noexcept;

        CNTDevice(CNTDevice const& other) = delete;
        CNTDevice(CNTDevice&& other) noexcept = default;

        CNTDevice& operator=(CNTDevice const& other) = delete;
        CNTDevice& operator=(CNTDevice&& other) noexcept = default;

        ~CNTDevice() noexcept;

        [[nodiscard]] OptionalCount get_count() const noexcept;
        [[nodiscard]] OptionalCount get_count_difference() const noexcept;

    private:
        Count get_current_count() const noexcept;

        void initialize() noexcept;
        void deinitialize() noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};
        Count counter_period_{};

        Count mutable count_{};
    };

}; // namespace Motors::Utility

#endif // CNT_DEVICE_HPP