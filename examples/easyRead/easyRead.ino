#include <IR.h>

IR ir;

void setup() {
  Serial.begin(9600);
  attachInterrupt(D6, portTick, FALLING);
}

void loop() {
  if (ir.isClick(0, true)) {
    Serial.print("Click ");
    Serial.println(ir.isClick(), HEX);
  }

  if (ir.isHolded(0, true)) {
    Serial.print("Holded ");
    Serial.println(ir.isHolded(), HEX);
  }

  if (ir.isHolding(0)) {
    Serial.print("Holding ");
    Serial.println(ir.isHolding(), HEX);
  }
}

IRAM_ATTR void portTick() {
  ir.tick();
}