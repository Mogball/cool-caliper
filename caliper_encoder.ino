#include <Arduino.h>

#define __NARG__(...) __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)

#define is_one_of2(x, a) \
  x == a
#define is_one_of3(x, a, b) \
  is_one_of2(x, a) || x == b
#define is_one_of4(x, a, b, c) \
  is_one_of3(x, a, b) || x == c
#define is_one_of5(x, a, b, c, d) \
  is_one_of4(x, a, b, c) || x == d
#define is_one_of6(x, a, b, c, d, e) \
  is_one_of5(x, a, b, c, d) || x == e
#define is_one_of7(x, a, b, c, d, e, f) \
  is_one_of6(x, a, b, c, d, e) || x == f
#define is_one_of8(x, a, b, c, d, e, f, g) \
  is_one_of7(x, a, b, c, d, e, f) || x == g
#define is_one_of9(x, a, b, c, d, e, f, g, h) \
  is_one_of8(x, a, b, c, d, e, f, g) || x == h
#define isnt_any_of2(x, a) \
  x != a
#define isnt_any_of3(x, a, b) \
  isnt_any_of2(x, a) && x != b
#define isnt_any_of4(x, a, b, c) \
  isnt_any_of3(x, a, b) && x != c
#define isnt_any_of5(x, a, b, c, d) \
  isnt_any_of4(x, a, b, c) && x != d

#define is_one_of(...) VFUNC(is_one_of, __VA_ARGS__)
#define isnt_any_of(...) VFUNC(isnt_any_of, __VA_ARGS__)

#define ENC_PIN_A  2
#define ENC_PIN_B  3
#define ENC_PIN_Ai 0
#define ENC_PIN_Bi 1

#define BTN_PIN  20
#define BTN_PINi 3

// LED Pins: 53 down to 46
// Digit Pins: 25, 24, 23, 22
#define _g_ 47
#define _f_ 48
#define _e_ 49
#define _d_ 50
#define _c_ 51
#define _b_ 52
#define _a_ 53

#define _A_ 22
#define _B_ 23
#define _C_ 24
#define _D_ 25

volatile int pos;

#define CCW(pos) ++pos
#define CW(pos) --pos
#define ZERO(pos) pos = 0

void activateOnly(int digit_pin) {
  digitalWrite(_A_, _A_ != digit_pin);
  digitalWrite(_B_, _B_ != digit_pin);
  digitalWrite(_C_, _C_ != digit_pin);
  digitalWrite(_D_, _D_ != digit_pin);
}

void writeDigit(uint8_t digit) {
  digitalWrite(_a_, isnt_any_of(digit, 1, 4));
  digitalWrite(_b_, isnt_any_of(digit, 5, 6));
  digitalWrite(_c_, isnt_any_of(digit, 2));
  digitalWrite(_d_, isnt_any_of(digit, 1, 4, 7, 9));
  digitalWrite(_e_, is_one_of(digit, 2, 6, 8, 0));
  digitalWrite(_f_, isnt_any_of(digit, 1, 2, 3, 7));
  digitalWrite(_g_, isnt_any_of(digit, 1, 7, 0));
}

void writeSign(bool neg) {
  digitalWrite(_a_, LOW);
  digitalWrite(_b_, LOW);
  digitalWrite(_c_, LOW);
  digitalWrite(_d_, LOW);
  digitalWrite(_e_, LOW);
  digitalWrite(_f_, LOW);
  digitalWrite(_g_, neg ? HIGH : LOW);
}

void setup() {
  pinMode(ENC_PIN_A, INPUT);
  pinMode(ENC_PIN_B, INPUT);
  pinMode(BTN_PIN, INPUT);

  for (int i = 22; i <= 25; ++i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  // 22: leftmost left
  // 23: leftmost right
  // 24: rightmost left
  // 25: rightmost right
  for (int i = 46; i <= 53; ++i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  // 46: POINT
  // 47: g
  // 48: f
  // 49: e
  // 50: d
  // 51: c
  // 52: b
  // 53: a

  digitalWrite(BTN_PIN, HIGH);
  
  attachInterrupt(ENC_PIN_Ai, interruptA, CHANGE);
  attachInterrupt(ENC_PIN_Bi, interruptB, CHANGE);
  attachInterrupt(BTN_PINi, interruptBtn, CHANGE);
}

#define RENDER_DELAY delay(5)

void setDigit(int digit_pin, uint8_t digit) {
  activateOnly(digit_pin);
  writeDigit(digit);
  RENDER_DELAY;
}

void negative() {
  activateOnly(_A_);
  writeSign(true);
  RENDER_DELAY;
}

void positive() {
  activateOnly(_A_);
  writeSign(false);
  RENDER_DELAY;
}

void writeInt(int g) {
  if (g > 999) { g = 999; }
  else if (g < -999) { g = -999; }
  if (g < 0) {
    g = -g;
    negative();  
  } else {
    positive();
  }
  setDigit(_D_, g % 10);
  setDigit(_C_, (g / 10) % 10);
  setDigit(_B_, (g / 100) % 10);
}

void loop() {
  writeInt(pos);
}

void interruptA() {
  if (digitalRead(ENC_PIN_A) == HIGH) {
    if (digitalRead(ENC_PIN_B) == LOW) { CCW(pos); } 
    else { CW(pos); }
  } else {
    if (digitalRead(ENC_PIN_B) == HIGH) { CCW(pos); }
    else { CW(pos); }
  }
}

void interruptB() {
  if (digitalRead(ENC_PIN_B) == HIGH) {
    if (digitalRead(ENC_PIN_A) == HIGH) { CCW(pos); }
    else { CW(pos); }
  } else {
    if (digitalRead(ENC_PIN_A) == LOW) { CCW(pos); }
    else { CW(pos); }
  }
}

void interruptBtn() {
  if (digitalRead(BTN_PIN) == HIGH) { ZERO(pos); }
}

