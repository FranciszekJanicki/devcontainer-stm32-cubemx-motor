#include "l298n.hpp"
#include "h_bridge.hpp"
#include <algorithm>
#include <cassert>
#include <expected>
#include <ranges>
#include <utility>

using namespace Motors;
using Direction = L298N::Direction;
using Channel = L298N::Channel;
using HBridgeChannel = L298N::HBridgeChannel;
using Raw = L298N::Raw;
using Voltage = L298N::Voltage;
using Direction = L298N::Direction;

namespace Motors {

    void L298N::reset() const noexcept
    {
        std::ranges::for_each(this->h_bridge_channels, [](auto& h_bridge_channel) {
            h_bridge_channel.h_bridge.set_fast_stop_direction();
            h_bridge_channel.h_bridge.set_min_voltage();
        });
    }

    void L298N::set_voltage(Channel const channel, Voltage const voltage) const noexcept
    {
        this->get_h_bridge(channel).set_voltage(voltage);
    }

    void L298N::set_max_voltage(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_max_voltage();
    }

    void L298N::set_min_voltage(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_min_voltage();
    }

    void L298N::set_direction(Channel const channel, Direction const direction) const noexcept
    {
        this->get_h_bridge(channel).set_direction(direction);
    }

    void L298N::set_forward_direction(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_forward_direction();
    }

    void L298N::set_backward_direction(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_backward_direction();
    }

    void L298N::set_soft_stop_direction(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_soft_stop_direction();
    }

    void L298N::set_fast_stop_direction(Channel const channel) const noexcept
    {
        this->get_h_bridge(channel).set_fast_stop_direction();
    }

    HBridge const& L298N::get_h_bridge(Channel const channel) const noexcept
    {
        if (const auto it{std::ranges::find_if(
                std::as_const(this->h_bridge_channels),
                [channel](auto const& h_bridge_channel) { return h_bridge_channel.channel == channel; })};
            it != this->h_bridge_channels.cend()) {
            return it->h_bridge;
        }
        std::unreachable();
    }

    HBridge& L298N::get_h_bridge(Channel const channel) noexcept
    {
        if (auto it{std::ranges::find_if(
                this->h_bridge_channels,
                [channel](auto const& h_bridge_channel) { return h_bridge_channel.channel == channel; })};
            it != this->h_bridge_channels.cend()) {
            return it->h_bridge;
        }
        std::unreachable();
    }

}; // namespace Motors