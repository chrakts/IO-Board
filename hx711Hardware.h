#ifndef HX711HARDWARE_H_INCLUDED
#define HX711HARDWARE_H_INCLUDED

// Hardware-Pins vom HX711
#define hx711Port           (&PORTD)
#define hx711_SCK           PIN7_bm
#define hx711_DIN           PIN6_bm
#define hx711_PINCTRL       PIN6CTRL
// Interrupt-Einstellungen
#define hx711Interrupt      PORTD_INT1_vect
#define hx711IntLevel       PORT_INT1LVL_HI_gc
#define hx711IntOn          hx711IntLevel
#define hx711IntOff         0b11110011
#define hx711Flag           PORT_INT1IF_bm
#define hx711IntMask        INT1MASK
#define hx711_DATA_BITS     24

// Einstellungen für die Tare-Funktion
#define hx711TareInterrupt  PORTD_INT0_vect
#define hx711TareIntLevel   PORT_INT0LVL_LO_gc
#define hx711TareFlag       PORT_INT0IF_bm
#define hx711TareIntMask    INT0MASK
#define AVERAGE_OVER        32

#define hx711TarePort       (&PORTD)
#define hx711TarePin        PIN0_bm
#define hx711_TAREPINCTRL   PIN0CTRL

#endif // HX711HARDWARE_H_INCLUDED

