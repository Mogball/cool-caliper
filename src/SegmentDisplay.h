#ifndef COOL_CALIPER_SEGMENTDISPLAY_H
#define COOL_CALIPER_SEGMENTDISPLAY_H

#include <Cosa/OutputPin.hh>

#include <wlib/stl/Tuple.h>

template<int ...pins>
wlp::RepeatTuple<OutputPin, sizeof...(pins)> make_pin_tuple() {
    return wlp::make_tuple(OutputPin(static_cast<Board::DigitalPin>(pins))...);
};

template<typename tuple_t, wlp::size_type i = wlp::tuple_size<tuple_t>::value>
struct for_each {
    template<typename functor_t>
    static void apply(tuple_t tuple, functor_t functor) {
        constexpr wlp::size_type size = wlp::tuple_size<tuple_t>::value;
        functor(wlp::get<size - i>(tuple));
        for_each<tuple_t, i - 1>::apply(tuple, functor);
    }
};

template<typename tuple_t>
struct for_each<tuple_t, 0> {
    template<typename functor_t>
    static void apply(tuple_t, functor_t) {}
};

template<
    typename tuple_t,
    wlp::size_type i = 0,
    wlp::size_type bound = wlp::tuple_size<tuple_t>::value,
    bool = bound == i
>
struct for_each_of {
    template<typename functor_t>
    static void apply(tuple_t tuple, functor_t functor) {
        functor(wlp::get<i>(tuple));
        for_each_of<tuple_t, i + 1, bound>::apply(tuple, functor);
    }
};

template<
    typename tuple_t,
    wlp::size_type i,
    wlp::size_type bound
>
struct for_each_of<tuple_t, i, bound, true> {
    template<typename functor_t>
    static void apply(tuple_t, functor_t) {}
};

class SegmentDisplay {
    enum Segment {
        dec = Board::D46,
        g, f, e, d, c, b, a
    };

    enum Digit {
        A = Board::D22,
        B, C, D
    };

    wlp::RepeatTuple<OutputPin, 8> m_segs = make_pin_tuple<53, 52, 51, 50, 49, 48, 47, 46>();
    wlp::RepeatTuple<OutputPin, 4> m_digs = make_pin_tuple<22, 23, 24, 25>();

    void activate_only(Board::DigitalPin digit_pin);

    void write_digit(uint8_t digit, bool dec = false);

    void write_sign(bool negative);

    void set_digit(int digit_pin, uint8_t digit, bool dec = false);

    void set_sign(bool negative);

    inline void render_delay() {
        delay(5);
    }

public:
    void begin();

    void write_int(int g);

    void write_double(double f);
};

#endif //COOL_CALIPER_SEGMENTDISPLAY_H
