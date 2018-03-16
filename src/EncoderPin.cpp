#include "EncoderPin.h"
#include "Encoder.h"

EncoderPin::EncoderPin(Encoder *encoder, Channel channel) :
    PinChangeInterrupt(
        channel == A
        ? Board::InterruptPin::PCI0
        : Board::InterruptPin::PCI1
    ),
    m_encoder(encoder),
    m_channel(channel) {}

void EncoderPin::on_interrupt(uint16_t) {
    m_encoder->channel_interrupt(m_channel);
}
