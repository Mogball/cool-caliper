#ifndef COOL_CALIPER_RESETPIN_H
#define COOL_CALIPER_RESETPIN_H

#include <Cosa/PinChangeInterrupt.hh>

class Encoder;

class ResetPin : public PinChangeInterrupt {
    Encoder *m_encoder;

public:
    ResetPin();

    void on_interrupt(uint16_t arg) override;

};

#endif //COOL_CALIPER_RESETPIN_H
