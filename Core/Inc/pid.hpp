#ifndef PID_HPP
#define PID_HPP

#include <algorithm>
#include <concepts>
#include <numeric>
#include <stdexcept>
#include <utility>

namespace Motors::Utility {

    template <typename Value>
    [[nodiscard]] auto derivative(Value const value, Value const prev_value, Value const dt) -> Value
    {
        if (dt == Value{0}) {
            std::unreachable();
        }
        return (value - prev_value) / dt;
    }

    template <typename Value>
    [[nodiscard]] auto integral(Value const value, Value const prev_value, Value const dt) noexcept -> Value
    {
        return (value + prev_value) / 2.0F * dt;
    }

    template <typename Value>
    struct PID {
        [[nodiscard]] auto operator()(Value const error, Value const dt) noexcept -> Value
        {
            return this->get_control(error, dt);
        }

        auto get_control(Value const error, Value const dt) noexcept -> Value
        {
            auto control{this->kp * error + this->ki * this->get_integral(error, dt) +
                         this->kd * this->get_derivative(error, dt)};
            auto sat_control{std::clamp(control, -this->saturation, this->saturation)};
            this->prev_sat_error = control - sat_control;
            return sat_control;
        }

        auto get_derivative(Value const error, Value const dt) noexcept -> Value
        {
            return derivative(error, std::exchange(this->prev_error, error), dt);
        }

        auto get_integral(Value const error, Value const dt) noexcept -> Value
        {
            auto integrated{this->ki == Value{0} ? error : error - this->kc * this->prev_sat_error / this->ki};
            return this->prev_integral += integral(integrated, std::exchange(this->prev_integrated, integrated), dt);
        }

        Value kp{};
        Value ki{};
        Value kd{};
        Value kc{};
        Value saturation{};

        Value prev_integral{0.0F};
        Value prev_error{0.0F};
        Value prev_sat_error{0.0F};
        Value prev_integrated{0.0F};
    };

}; // namespace Motors::Utility

#endif // PID_HPP
