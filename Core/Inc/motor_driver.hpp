#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include "dc_motor.hpp"
#include "encoder.hpp"
#include "pid.hpp"
#include <utility>

namespace Motors {

    struct MotorDriver {
    public:
        using Value = DCMotor::Voltage;
        using Direction = DCMotor::Direction;
        using Regulator = Utility::PID<Value>;
        using SpeedToVoltage = Value (*)(Value) noexcept;
        using SpeedToDirection = Direction (*)(Value) noexcept;

        void operator()(Value const input_speed, Value const dt) noexcept;

        Regulator regulator{};
        DCMotor motor{};
        Encoder encoder{};

        SpeedToVoltage speed_to_voltage{nullptr};
        SpeedToDirection speed_to_direction{nullptr};

    private:
        void set_voltage(Value const control_speed) const noexcept;
        void set_speed(Value const control_speed) const noexcept;
        void set_direction(Value const control_speed) const noexcept;

        Value get_measured_speed(Value const dt) noexcept;
        Value get_control_speed(Value const error_speed, Value const dt) noexcept;
        Value get_error_speed(Value const input_speed, Value const dt) noexcept;
    };

}; // namespace Motors

#endif // MOTOR_DRIVER_HPP