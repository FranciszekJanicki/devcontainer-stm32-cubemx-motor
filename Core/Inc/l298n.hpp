#ifndef L298N_HPP
#define L298N_HPP

#include "h_bridge.hpp"
#include "utility.hpp"
#include <array>
#include <cmath>
#include <cstdint>
#include <utility>

namespace Motors {

    struct L298N {
    public:
        enum struct Channel : std::uint8_t {
            CHANNEL_A,
            CHANNEL_B,
        };

        struct HBridgeChannel {
            Channel channel{};
            HBridge h_bridge{};
        };

        using Direction = HBridge::Direction;

        void reset() const noexcept;

        void set_voltage(Channel const channel, float const voltage) const noexcept;
        void set_max_voltage(Channel const channel) const noexcept;
        void set_min_voltage(Channel const channel) const noexcept;

        void set_direction(Channel const channel, Direction const direction) const noexcept;
        void set_forward_direction(Channel const channel) const noexcept;
        void set_backward_direction(Channel const channel) const noexcept;
        void set_soft_stop_direction(Channel const channel) const noexcept;
        void set_fast_stop_direction(Channel const channel) const noexcept;

        std::array<HBridgeChannel, 2UL> h_bridge_channels{};

    private:
        HBridge const& get_h_bridge(Channel const channel) const noexcept;
        HBridge& get_h_bridge(Channel const channel) noexcept;
    };

}; // namespace Motors

#endif // L298N_HPP