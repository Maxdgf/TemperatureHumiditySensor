# TemperatureHumiditySensor
Simple 🌡️💧temperature and humidity sensor created on Arduino UNO, capable of measuring the current temperature and humidity, as well as reflecting the acceptability of humidity and temperature with a color signal via RGB LED.

# Scheme📋
![](github/arduinoTempHumSensor.png)

## Used components🔌:

- Arduino UNO
- LCD1602 I2C
- DHT11
- RGB LED 

| Component    | Pins                              |
| :----------- | :-------------------------------- |
| `LCD1602 I2C`| **GND** -> GND, **VCC** -> 5V, **SDA** -> A4, **SCL** -> A5 |
| `DHT11`      | **S** -> pin7, **VCC** -> 5V, **GND** -> GND |
| `RGB LED`    | **R** -> pin8, **G** -> pin9, **B** -> pin10, **GND** -> GND |
