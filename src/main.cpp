#include <Cosa/RTT.hh>

#include "Encoder.h"
#include "SegmentDisplay.h"

SegmentDisplay display;
Encoder encoder;

void setup() {
    RTT::begin();
    display.begin();
    encoder.begin();
}

void loop() {
}
