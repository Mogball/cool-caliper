#include "ResetPin.h
#include "Encoder.h"

ResetPin::ResetPin() :
    PinChangeInterrupt(Board::PCI3) {}

void ResetPin::on_interrupt(uint16_t) {
    m_encoder->reset_interrupt();
}
