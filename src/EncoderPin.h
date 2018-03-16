#ifndef COOL_CALIPER_ENCODERPIN_H
#define COOL_CALIPER_ENCODERPIN_H

#include <Cosa/PinChangeInterrupt.hh>

class Encoder;

class EncoderPin : public PinChangeInterrupt {
public:
    enum Channel {
        A, B
    };

private:
    Encoder *m_encoder;
    Channel m_channel;

public:
    EncoderPin(Encoder *encoder, Channel channel);

    void on_interrupt(uint16_t arg) override;
};


#endif //COOL_CALIPER_ENCODERPIN_H
