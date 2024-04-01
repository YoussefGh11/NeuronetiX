# NeuronetiX

Smart home: • it is a popular project nowadays, it is a very comfortable
application for humans, it aims to convert anything around to be controllable and
smart. • At the following we have some requirement to implement smart home
application: ❑ Remoted controlled by mobile or lab top. ❑ For emergency cases
or controlling without mobile or lap-top use LCD and Keypad “user mode only”.
❑ The controllable things are 6 lamps “5 on/off lamps, one dimming lamp”, door,
air-condition according to the ambient temperature.
❑ Login system admin and user “admin is remoted only”. ❑ Admin mode can
register any user or remove. ❑ Usernames and password must be kept into
memory even if the system is powered off. ❑ If admin or any user or passwords
are entered wrong more than 3 trial, the system must break down and fire alarm
until reset. ❑ Admin and user can access to all applies except user cannot
control the door opening.
Specifications –LCD& keypad:
1. They are used to login to system as a user only.
2. After login, user can control all features except opening door.
3. They can control the system even if any user login by remoted mode except
 admin until allowing of admin.
4. The interfacing of LCD must display the running devices if the keypad-LCD
 system is not used. 5. The user’s usernames in this system different than
 the user’s usernames in the remoting system.
Embedded-System Internship 5
Specifications –EEPROM:
1. Storing the new user to the system “registration”.
2. It must be Read/write in admin mode.
3. It must be read only in user mode.
Specifications –TTL/Bluetooth:
1. Transmitting/Receiving between MC and PC/mobile.
2. Every action, Message must be printed on Mobile/PC screen, like:
 Hey, please Enter your username:
3. Transmitting/Receiving the commands to run the system.
Specifications –Lamps, Relay, Dimmer:
1. Lamps must be isolated because of high power.
2. Dimmer is a circuit that can control on the current flow to lamp depending on
 the input voltage “0 – 5V”.
Specifications –Temperature Sensor, DC motor:
1. Temperature sensor reads the ambient temperature, if the temperature is
higher than 28 °C, Air condition must be run “DC motor”, if the temperature
becomes lower than 21 °C, Air condition must be turned off “DC motor”.
Specifications – Door:
1. The actuator used is a servo motor to control the opening door only in admin
mode, it is controlled by command which is send by Mobile/PC “Open\Close the
door”
Component you may need:
1. (AVR/ARM) and 24C08 EEPROM, or use the internal.
 2. Bluetooth module HC-05 or TTL (PL2003 or CH340or CP2102).
 3. 5 transistors and relays (Not mandatory they can be replaced by LEDs.
 4. 1 transistor and Solid-state Relay for dimming circuit.
5. LM35 temperature sensor or equivalent.
6. 2 NPN and DC motor
 7. Keypad & Lm01602A Character LCD.
Embedded-System Internship 6
8. Servo motor.
