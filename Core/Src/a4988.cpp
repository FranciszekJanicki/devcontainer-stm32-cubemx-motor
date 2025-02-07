#include "a4988.hpp"
#include "stm32l4xx_hal.h"
#include "utility.hpp"

namespace Motors {

    A4988::A4988(GPIOHandle const gpio,
                 std::uint16_t const ms1,
                 std::uint16_t const ms2,
                 std::uint16_t const ms3,
                 std::uint16_t const reset,
                 std::uint16_t const sleep,
                 std::uint16_t const step,
                 std::uint16_t const dir,
                 std::uint16_t const enable) noexcept :
        ms1_{ms1}, ms2_{ms2}, ms3_{ms3}, reset_{reset}, sleep_{sleep}, step_{step}, dir_{dir}, enable_{enable}
    {
        this->initialize();
    }

    A4988::~A4988() noexcept
    {
        this->deinitialize();
    }

    void A4988::trigger_next_step(Direction const direction, StepRes const step_res) const noexcept
    {
        this->set_direction(direction);
        this->set_step_res(step_res);
        this->set_step(true);
    }

    void A4988::initialize() noexcept
    {
        if (this->gpio_ != nullptr) {
            this->set_reset(true);
            this->set_enable(true);
            this->set_sleep(false);
            this->set_step(false);
            this->initialized_ = true;
        }
    }

    void A4988::deinitialize() noexcept
    {
        if (this->gpio_ != nullptr) {
            this->set_reset(true);
            this->set_enable(false);
            this->set_sleep(true);
            this->set_step(false);
            this->initialized_ = false;
        }
    }

    void A4988::set_step(bool const step) const noexcept
    {
        if (this->initialized_) {
            if (step) {
                HAL_GPIO_WritePin(this->gpio_, this->step_, GPIO_PinState::GPIO_PIN_SET);
                HAL_Delay(10UL);
            }
            HAL_GPIO_WritePin(this->gpio_, this->step_, GPIO_PinState::GPIO_PIN_RESET);
        }
    }

    void A4988::set_step_res(StepRes const step_res) const noexcept
    {
        switch (step_res) {
            case StepRes::FULL:
                this->set_full_step_res();
                break;
            case StepRes::HALF:
                this->set_half_step_res();
                break;
            case StepRes::QUARTER:
                this->set_quarter_step_res();
                break;
            case StepRes::EIGHTH:
                this->set_eighth_step_res();
                break;
            case StepRes::SIXTEENTH:
                this->set_sixteenth_step_res();
                break;
            default:
                break;
        }
    }

    void A4988::set_full_step_res() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->ms1_ | this->ms2_ | this->ms3_, GPIO_PinState::GPIO_PIN_RESET);
        }
    }

    void A4988::set_half_step_res() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->ms1_, GPIO_PinState::GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio_, this->ms2_ | this->ms3_, GPIO_PinState::GPIO_PIN_RESET);
        }
    }

    void A4988::set_quarter_step_res() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->ms1_ | this->ms3_, GPIO_PinState::GPIO_PIN_RESET);
            HAL_GPIO_WritePin(this->gpio_, this->ms2_, GPIO_PinState::GPIO_PIN_SET);
        }
    }

    void A4988::set_eighth_step_res() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->ms1_ | this->ms2_, GPIO_PinState::GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio_, this->ms3_, GPIO_PinState::GPIO_PIN_RESET);
        }
    }

    void A4988::set_sixteenth_step_res() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->ms1_ | this->ms2_ | this->ms3_, GPIO_PinState::GPIO_PIN_SET);
        }
    }

    void A4988::set_direction(Direction const direction) const noexcept
    {
        switch (direction) {
            case Direction::FORWARD:
                this->set_forward_direction();
                break;
            case Direction::BACKWARD:
                this->set_backward_direction();
                break;
            default:
                break;
        }
    }

    void A4988::set_forward_direction() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->dir_, GPIO_PinState::GPIO_PIN_RESET);
        }
    }

    void A4988::set_backward_direction() const noexcept
    {
        if (this->initialized_) {
            HAL_GPIO_WritePin(this->gpio_, this->dir_, GPIO_PinState::GPIO_PIN_SET);
        }
    }

    void A4988::set_reset(bool const reset) const noexcept
    {
        HAL_GPIO_WritePin(this->gpio_,
                          this->reset_,
                          reset ? GPIO_PinState::GPIO_PIN_RESET : GPIO_PinState::GPIO_PIN_SET);
    }

    void A4988::set_enable(bool const enable) const noexcept
    {
        HAL_GPIO_WritePin(this->gpio_,
                          this->enable_,
                          enable ? GPIO_PinState::GPIO_PIN_RESET : GPIO_PinState::GPIO_PIN_SET);
    }

    void A4988::set_sleep(bool const sleep) const noexcept
    {
        HAL_GPIO_WritePin(this->gpio_,
                          this->sleep_,
                          sleep ? GPIO_PinState::GPIO_PIN_RESET : GPIO_PinState::GPIO_PIN_SET);
    }

}; // namespace Motors