#ifndef A4988_HPP
#define A4988_HPP

#include "stm32l4xx_hal.h"
#include "utility.hpp"
#include <cstdint>

namespace Motors {

    struct A4988 {
    public:
        enum struct StepRes : std::uint8_t {
            FULL,
            HALF,
            QUARTER,
            EIGHTH,
            SIXTEENTH,
        };

        enum struct Direction : std::uint8_t {
            FORWARD,
            BACKWARD,
        };

        A4988() noexcept = default;
        A4988(Utility::GPIOHandle const gpio,
              std::uint16_t const ms1,
              std::uint16_t const ms2,
              std::uint16_t const ms3,
              std::uint16_t const reset,
              std::uint16_t const sleep,
              std::uint16_t const step,
              std::uint16_t const dir,
              std::uint16_t const enable) noexcept;

        A4988(A4988 const& other) = delete;
        A4988(A4988&& other) noexcept = default;

        A4988& operator=(A4988 const& other) = delete;
        A4988& operator=(A4988&& other) noexcept = default;

        ~A4988() noexcept;

        void trigger_next_step(Direction const direction, StepRes const step_res) const noexcept;

    private:
        static constexpr std::uint64_t COUNTER_PERIOD{1000UL};

        void initialize() noexcept;
        void deinitialize() noexcept;

        void set_step_res(StepRes const step_res) const noexcept;
        void set_full_step_res() const noexcept;
        void set_half_step_res() const noexcept;
        void set_quarter_step_res() const noexcept;
        void set_eighth_step_res() const noexcept;
        void set_sixteenth_step_res() const noexcept;

        void set_direction(Direction const direction) const noexcept;
        void set_forward_direction() const noexcept;
        void set_backward_direction() const noexcept;

        void set_reset(bool const reset) const noexcept;
        void set_enable(bool const enable) const noexcept;
        void set_sleep(bool const sleep) const noexcept;
        void set_step(bool const step) const noexcept;

        Utility::GPIOHandle gpio_{nullptr};
        std::uint16_t ms1_{};
        std::uint16_t ms2_{};
        std::uint16_t ms3_{};
        std::uint16_t reset_{};
        std::uint16_t sleep_{};
        std::uint16_t step_{};
        std::uint16_t dir_{};
        std::uint16_t enable_{};

        bool initialized_{false};
    };

}; // namespace Motors

#endif // A4988_HPP