#ifndef EFR32FG13_GPIO_H_
#define EFR32FG13_GPIO_H_

#include "../../../efr32/vendor/em_device.h"

/** GPIO ports identificator. */
typedef enum
{
  GPIOA = 0, /**< Port A */
  GPIOB = 1, /**< Port B */
  GPIOC = 2, /**< Port C */
  GPIOD = 3, /**< Port D */
  GPIOE = 4, /**< Port E */
  GPIOF = 5, /**< Port F */
  GPIOG = 6, /**< Port G */
  GPIOH = 7, /**< Port H */
  GPIOI = 8, /**< Port I */
  GPIOJ = 9, /**< Port J */
  GPIOK = 10 /**< Port K */
} hal_gpio_port_e;

/** Pin mode. For more details on each mode, please refer to the EFR32XG13
 * reference manual. */
typedef enum
{
  /** Input disabled. Pullup if DOUT is set. */
  GPIO_MODE_DISABLED        = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set */
  GPIO_MODE_IN_OD_NOPULL    = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction */
  GPIO_MODE_IN_PULL         = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction */
  GPIO_MODE_IN_PP           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output */
  GPIO_MODE_OUT_PP          = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Wired-or output with pull-down */
  GPIO_MODE_OUT_OS_PD       = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output with pullup */
  GPIO_MODE_OUT_OD_PU       = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output */
  GPIO_MODE_OUT_OD_NOPULL   = _GPIO_P_MODEL_MODE0_WIREDAND,
} hal_gpio_mode_e;

__STATIC_INLINE uint32_t hal_gpio_get(hal_gpio_port_e port, uint32_t pin)
{
    return((uint32_t)((GPIO->P[port].DIN >> pin) & 0x1));
}

__STATIC_INLINE uint32_t hal_gpio_get_dout(hal_gpio_port_e port, uint32_t pin)
{
    return((uint32_t)((GPIO->P[port].DOUT >> pin) & 0x1));
}

__STATIC_INLINE void hal_gpio_set(hal_gpio_port_e port, uint32_t pin)
{
    GPIO->P[port].DOUT |= (1 << pin);
}

__STATIC_INLINE void hal_gpio_clear(hal_gpio_port_e port, uint32_t pin)
{
    GPIO->P[port].DOUT &= ~(1 << pin);
}

__STATIC_INLINE void hal_gpio_toggle(hal_gpio_port_e port, uint32_t pin)
{
    GPIO->P[port].DOUTTGL = 1 << pin;
}

__STATIC_INLINE void hal_gpio_set_mode(hal_gpio_port_e port,
                                       uint32_t pin,
                                       hal_gpio_mode_e mode)
{
    if (pin < 8)
    {
        GPIO->P[port].MODEL =
        (GPIO->P[port].MODEL & ~(0xF << (pin * 4))) | (mode << (pin * 4));
    }
    else
    {
        GPIO->P[port].MODEH =
        (GPIO->P[port].MODEH & ~(0xF << ((pin - 8) * 4))) |
                                (mode << ((pin - 8) * 4));
    }
}

#endif /* EFR32FG13_GPIO_H_ */
