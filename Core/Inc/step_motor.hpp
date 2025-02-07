#ifndef STEP_MOTOR_HPP
#define STEP_MOTOR_HPP

#include "a4988.hpp"
#include "pid.hpp"
#include <cstdint>

namespace Motors {

    struct StepMotor {
    public:
        void operator()(float const input_speed, float const sampling_time) noexcept;

        A4988 a4988{};
        std::uint32_t step_count{};

    private:
        void set_voltage(float const control_speed) const noexcept;
        void set_speed(float const control_speed) const noexcept;
        void set_direction(float const control_speed) const noexcept;

        float get_measured_speed(float const sampling_time) noexcept;
        float get_control_speed(float const error_speed, float const sampling_time) noexcept;
        float get_error_speed(float const input_speed, float const sampling_time) noexcept;
    };

}; // namespace Motors

#endif // STEP_MOTOR_HPP
