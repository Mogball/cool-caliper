#include <math.h>
#include <wlib/utility/Compare.h>

#include "SegmentDisplay.h"

using namespace wlp;

struct digit_on_functor {
    uint8_t m_pin;

    explicit digit_on_functor(Board::DigitalPin pin) :
        m_pin(pin) {}

    void operator()(OutputPin &pin) {
        pin.write(pin.pin() == m_pin);
    }
};

struct seg {
    typedef isnt_any_of<uint8_t, 1, 4> a;
    typedef isnt_any_of<uint8_t, 5, 6> b;
    typedef isnt_any_of<uint8_t, 2> c;
    typedef isnt_any_of<uint8_t, 1, 4, 7, 9> d;
    typedef is_one_of<uint8_t, 2, 6, 8, 0> e;
    typedef isnt_any_of<uint8_t, 1, 2, 3, 7> f;
    typedef isnt_any_of<uint8_t, 1, 7, 0> g;

    void operator()(OutputPin &pin) {}
};

struct write_zero_functor {
    void operator()(OutputPin &pin) {
        pin.write(0);
    }
};

void SegmentDisplay::begin() {}

void SegmentDisplay::activate_only(Board::DigitalPin digit_pin) {
    for_each<decltype(m_digs)>::apply(m_digs, digit_on_functor(digit_pin));
}

void SegmentDisplay::write_digit(uint8_t digit, bool dec) {
    get<0>(m_segs).write(seg::a::apply(digit));
    get<1>(m_segs).write(seg::b::apply(digit));
    get<2>(m_segs).write(seg::c::apply(digit));
    get<3>(m_segs).write(seg::d::apply(digit));
    get<4>(m_segs).write(seg::e::apply(digit));
    get<5>(m_segs).write(seg::f::apply(digit));
    get<6>(m_segs).write(seg::g::apply(digit));
    get<7>(m_segs).write(dec);
}

void SegmentDisplay::write_sign(bool negative) {
    for_each_of<decltype(m_segs), 0, 6>::apply(m_segs, write_zero_functor());
    get<6>(m_segs).write(negative);
}

void SegmentDisplay::set_digit(int digit_pin, uint8_t digit, bool dec) {
    activate_only(static_cast<Board::DigitalPin>(digit_pin));
    write_digit(digit, dec);
    render_delay();
}

void SegmentDisplay::write_int(int g) {
    g = abs(g);
    set_digit(D, static_cast<uint8_t>(g % 10));
    set_digit(C, static_cast<uint8_t>((g / 10) % 10));
    set_digit(B, static_cast<uint8_t>((g / 100)  % 10));
    set_digit(A, static_cast<uint8_t>((g / 1000) % 10));
}

void SegmentDisplay::write_double(double f) {
    auto iv = static_cast<int>(round(abs(f) * 100));
    set_digit(D, static_cast<uint8_t>(iv % 10));
    set_digit(C, static_cast<uint8_t>((iv / 10) % 10));
    set_digit(B, static_cast<uint8_t>((iv / 100) % 10), true);
    set_digit(A, static_cast<uint8_t>((iv / 1000) % 10));
}

void SegmentDisplay::set_sign(bool negative) {
    activate_only(static_cast<Board::DigitalPin>(A));
    write_sign(negative);
    render_delay();
}
