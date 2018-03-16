#include <Cosa/RTT.hh>

#include "Encoder.h"
#include "SegmentDisplay.h"

SegmentDisplay display;
Encoder encoder;

double calibration = 0.258754;

void setup() {
    RTT::begin();
    display.begin();
    encoder.begin();
}

void loop() {
    int pos = encoder.get_pos();
    double len = pos * calibration;
    display.write_double(len);
}
