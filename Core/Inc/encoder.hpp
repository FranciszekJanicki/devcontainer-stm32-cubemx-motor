#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "cnt_device.hpp"
#include "utility.hpp"
#include <cmath>
#include <cstdint>
#include <optional>
#include <utility>

namespace Motors {

    struct Encoder {
    public:
        using Count = Utility::CNTDevice::Count;
        using Angle = std::float_t;
        using Speed = std::float_t;
        using OptionalAngle = std::optional<Angle>;
        using OptionalSpeed = std::optional<Speed>;

        [[nodiscard]] OptionalAngle get_angle_degrees() const noexcept;
        [[nodiscard]] OptionalAngle get_angle_radians() const noexcept;
        [[nodiscard]] OptionalSpeed get_speed_degrees(float const dt) const noexcept;
        [[nodiscard]] OptionalSpeed get_speed_radians(float const dt) const noexcept;

        Utility::CNTDevice cnt_device{};

        Count counts_per_pulse{};
        Count pulses_per_360{};

    private:
        Angle count_to_degrees(Count const count) const noexcept;
        Angle count_to_degree_diff(Count const count_diff) const noexcept;
    };

}; // namespace Motors

#endif // ENCODER_HPP