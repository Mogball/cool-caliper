#include "Encoder.h"

Encoder::Encoder() :
    pos(0),
    pin_A(this, EncoderPin::A),
    pin_B(this, EncoderPin::B) {}

void Encoder::channel_interrupt(EncoderPin::Channel channel) {
    if (channel == EncoderPin::A) {
        if (pin_A.read() == !pin_B.read()) { ccw(); }
        else { cw(); }
    } else {
        if (pin_B.read() == pin_A.read()) { ccw(); }
        else { cw(); }
    }
}

void Encoder::reset_interrupt() {
    zero();
}

int Encoder::get_pos() const {
    return pos;
}

void Encoder::begin() {
    pin_A.begin();
    pin_B.begin();
}
