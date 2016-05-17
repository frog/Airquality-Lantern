# Airquality Lantern

Build your own Airquality Lantern.

## BOM
- 1x NODEMCU ESP-12E   https://item.taobao.com/item.htm?spm=a1z09.2.0.0.5Y01U2&id=520415138322
- 1x plantower pms3003 https://item.taobao.com/item.htm?spm=a1z09.2.0.0.5Y01U2&id=524445086102
- 1x ws2812 LED ring   https://item.taobao.com/item.htm?spm=a1z09.2.0.0.5Y01U2&id=44490546962
- A glass jar          (Found)
- 5v 2Amp Power supply (Found)


## Arduino/NodeMCU setup
- Arduino version required >= 1.6.9 http://arduino.cc
- https://github.com/esp8266/Arduino - install the esp8266 client
- Program with NodeMCU 1.0 ESP-12E board

## Libaries to install
- ArduinoJson           https://github.com/bblanchon/ArduinoJson
- NeoPixelBus           https://github.com/Makuna/NeoPixelBus
- PubSubClient          https://github.com/knolleary/pubsubclient

## Rapid Prototyping An Airquality Sensor
A pollution lantern that you can build and extend yourself from a hardware and software perspective for rapid prototyping. We took a low cost, ESP8266 in this case a nodemcu which includes its own processor, ram, onboard storage and WiFi in an all in one package, a PMS3003A PM2.5 particle sensor by Plantower and a WS2818 addressable LED ring all housed in a Glass Jar, powered by a 5V external power supply and communicating over WiFi by MQTT. All of these items you can find on taobao.

The lantern currently shows two states, one for red for – it’s time to turn on the air purifier and green if the air is within acceptable range.

*To plan for obsolescence* – where a remote service could be terminated. We wanted a Lantern that could work both online and offline. By default, we assume we will work offline and use our internal readings and only if the server tells us to change such as a user initiated change we use the server provided readings. We used an MQTT server such as Mosca (https://www.npmjs.com/package/mosca) which is a great Pub/Sub server to quickly get setup.

The PMS3003A communicates over serial at 9600 Baud every second, sending a byte encoded string that contains counts for 0.3~1.0um, 1.0~2.5um and 2.5~10um particle sizes, one thing to note is that these are not 100% accurate, in fact the data sheet mentions they are 50% accurate at 0.3um and 98% accurate at 0.5um or larger as it counts the particles passing through.

The PMS3003A should connect to the VIN and GND and the TX pin should connect to D5 on the Nodemcu. Additionally, the WS2818 should also be connected to the VIN and GND on Nodemcu and the data-in pin should be connected to the RX pin on Nodemcu documented in the photos.

Finally, on the wiring side we need to connect the VIN and GND of the Nodemcu to a 5V power supply capable of delivering up to 2Amps of power, once wired up it time to upload the firmware.

## A few notes: 
D5 pin will use a software serial to receive data from the PMS3003A sensor without blocking the ESP8266 from doing its other work such as maintaining wireless connectivity and running other functions.

Unconventional but The RX pin will be used for transmitting data to the WS2818 Led ring where we take advantage of the hardware over UART (GPIO2) to transfer data to the LED ring.

Since we do not have adequate cooling in our jar, it would be unwise to set the LED intensity over 30% as these are constant current.

