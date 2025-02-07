#ifndef SERVO_HPP
#define SERVO_HPP

#include "pwm_device.hpp"
#include "utility.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <utility>

namespace Motors {

    struct Servo {
    public:
        using PWMDevice = Utility::PWMDevice;
        using FloatToFloat = float (*)(float) noexcept;

        void set_angle(float const angle) const noexcept;
        void set_angle_max() const noexcept;
        void set_angle_min() const noexcept;

        template <typename... floats>
        void run_sequence(floats const... angles) noexcept
        {
            for (auto const angle : std::array<float, sizeof...(angles)>{angles...}) {
                this->set_angle(angle);
                HAL_Delay(50);
            }
        }

        FloatToFloat angle_to_voltage{nullptr};

        PWMDevice pwm_device{};
    };

}; // namespace Motors

#endif // SERVO_HPP