#ifndef DC_MOTOR_HPP
#define DC_MOTOR_HPP

#include "encoder.hpp"
#include "h_bridge.hpp"
#include "pid.hpp"
#include <utility>

namespace Motors {

    struct DCMotor {
    public:
        using Direction = HBridge::Direction;
        using Regulator = Utility::PID<float>;
        using FloatToFloat = float (*)(float) noexcept;
        using FloatToDirection = Direction (*)(float) noexcept;

        void operator()(float const input_speed, float const sampling_time) noexcept;

        Regulator regulator{};
        HBridge motor{};
        Encoder encoder{};

        FloatToFloat speed_to_voltage{nullptr};
        FloatToDirection speed_to_direction{nullptr};

    private:
        void set_voltage(float const control_speed) const noexcept;
        void set_speed(float const control_speed) const noexcept;
        void set_direction(float const control_speed) const noexcept;

        float get_measured_speed(float const sampling_time) noexcept;
        float get_control_speed(float const error_speed, float const sampling_time) noexcept;
        float get_error_speed(float const input_speed, float const sampling_time) noexcept;
    };

}; // namespace Motors

#endif // MOTOR_DRIVER_HPP