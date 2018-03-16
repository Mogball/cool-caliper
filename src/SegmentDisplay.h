#ifndef COOL_CALIPER_SEGMENTDISPLAY_H
#define COOL_CALIPER_SEGMENTDISPLAY_H

#include <Cosa/OutputPin.hh>

class SegmentDisplay {
    OutputPin m_a{Board::D53};
    OutputPin m_b{Board::D52};
    OutputPin m_c{Board::D51};
    OutputPin m_d{Board::D50};
    OutputPin m_e{Board::D49};
    OutputPin m_f{Board::D48};
    OutputPin m_g{Board::D47};
    OutputPin m_dec{Board::D46};

    enum Digit {
        A = 22,
        B = 23,
        C = 24,
        D = 25
    };

    void activate_only(Board::DigitalPin digit_pin);

    void write_digit(uint8_t digit);

    void write_sign(bool negative);

    void set_digit(int digit_pin)

public:
    void begin();
};

#endif //COOL_CALIPER_SEGMENTDISPLAY_H
