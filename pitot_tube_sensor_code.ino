#include "ms4525do.h"
#include "units.h"
#include <Wire.h>

#include <Wire.h>

#define MS4525_ADDR 0x28

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Reading pitot pressure..");
}

void loop() {
  Wire.requestFrom(MS4525_ADDR, 2);

  if (Wire.available() == 2) {
    uint8_t b1 = Wire.read();
    uint8_t b2 = Wire.read();

    // 14-bit pressure value
    uint16_t rawPressure = ((b1 & 0x3F) << 8) | b2;

    // Convert to Pascals (±1 psi sensor)
    float pressurePa = (rawPressure - 8192) * 6894.76 / 16384.0;
    float airDensity = 1.225;  // kg/m³, standard air at sea level
    float airspeed = sqrt(2 * pressurePa / airDensity);

    Serial.print("Airspeed (m/s): ");
    Serial.println(airspeed - 6.47); // airspeed print - 6.47 (average airspeed when pitot tube was stationary)

  } else {
    Serial.println("Read error");
  }

  delay(200);
}

