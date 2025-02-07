#include "encoder.hpp"
#include "utility.hpp"

namespace Motors {

    std::optional<float> Encoder::get_angle_degrees() const noexcept
    {
        return this->cnt_device.get_count().transform(
            [this](std::uint32_t const count) { return this->count_to_degrees(count); });
    }

    std::optional<float> Encoder::get_angle_radians() const noexcept
    {
        return this->get_angle_degrees().transform(&Utility::degrees_to_radians<float>);
    }

    std::optional<float> Encoder::get_speed_degrees(float const dt) const noexcept
    {
        return this->cnt_device.get_count_difference().transform(
            [this, dt](std::uint32_t const count_diff) { return this->count_to_degree_diff(count_diff) / dt; });
    }

    std::optional<float> Encoder::get_speed_radians(float const dt) const noexcept
    {
        return this->get_speed_degrees(dt).transform(&Utility::degrees_to_radians<Speed>);
    }

    float Encoder::count_to_degrees(std::uint32_t const count) const noexcept
    {
        return static_cast<float>(count) * 360.0F / static_cast<float>(this->pulses_per_360 * this->counts_per_pulse);
    }

    float Encoder::count_to_degree_diff(std::uint32_t const count_diff) const noexcept
    {
        return std::fmod(this->count_to_degrees(count_diff) + 360.0F, 360.0F);
    }

}; // namespace Motors