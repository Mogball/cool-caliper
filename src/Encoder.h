#ifndef COOL_CALIPER_ENCODER_H
#define COOL_CALIPER_ENCODER_H

#include "EncoderPin.h"

class Encoder {
    volatile int pos;

    friend class EncoderPin;
    friend class ResetPin;

    EncoderPin pin_A;
    EncoderPin pin_B;

    inline void ccw() {
        ++pos;
    }

    inline void cw() {
        --pos;
    }

    inline void zero() {
        pos = 0;
    }

    void channel_interrupt(EncoderPin::Channel channel);

    void reset_interrupt();

public:
    int get_pos() const;

    void begin();
};

#endif //COOL_CALIPER_ENCODER_H
