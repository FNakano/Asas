# A Guide to Tower Pro SG90 servo (normal and fail)

## Motivation

Information is scattered trough many sites. In special about unexpected behaviour like motor/driver heating and arm locking.

## Instructions and Results

SG90 Datasheet is in http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf (PDF format), https://docs.sunfounder.com/projects/umsk/en/latest/01_components_basic/33-component_servo.html (HTML format).

### Normal use

Connect servo BROWN wire is GND, RED wire is 5v (not 3V3), ORANGE wire is PWM CONTROL (e.g. ESP32 pin 25 https://github.com/JadnoABS/digitalLocker/tree/main)  

Servo PWM frequency is 50Hz. High logic level pulse width controls axis rotation (approximate) pulse width - angle correspondence are

| pulse width | angle (PDF reference) | angle (HTML reference) |
| --- | --- | --- |
| 1ms | -90 | --- |
| 1,5ms | zero (reference) | --- |
| 2ms | 90 | --- |
| 0,5ms | --- | zero (reference) |
| 1,5ms | --- | 90 |
| 2,5ms | --- | 180 |

There is some discrepancy between data in the references.

Next step is to generate pulses with controlled width on an ESP32.

#### About ESP32 PWM generation 

From ESP32 documentation we see that generate PWM signals is an interplay with hardware timers, clock frequency, interrupts,... (https://docs.espressif.com/projects/esp-idf/en/v5.0.2/esp32/api-reference/peripherals/ledc.html#ledc-api-configure-timer). PWM frequency and (achievable) duty cycles are interdepentent. For example, at 5kHz duty cycle resolution is 13 bits (https://docs.espressif.com/projects/esp-idf/en/v5.0.2/esp32/api-reference/peripherals/ledc.html#supported-range-of-frequency-and-duty-resolutions)

As a (risky) shortcut to use PWM on ESP32, analysing MicroPython v1.23.0 on 2024-06-02; Generic ESP32 module with ESP32,
PWM duty cycle range from 0 to almost 100% in steps in the range 0 to 1023 (information from the error message below). 

```
>>> s.motor.duty(1024)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: duty must be from 0 to 1023
```

Micropython PWM docs: https://docs.micropython.org/en/latest/library/machine.PWM.html

Measured the PWM output with an oscilloscope. Setting `s.motor.duty(1023)` does not result in a duty cycle of 100%. There is a 20us "gap" in the waveform. This may be a rounding error or may be an expected behavior. This question (is it a rounding error or an expected behavior?) motivate some experiments.


The range usable for SG90, according to some reference, is 23-126. An experiment was done. The range is a bit different. See https://github.com/FNakano/Asas/blob/main/guideToSG90.md#esp32-with-micropython-pwm-experiments . In practical use the values may vary. Program should provide appropriate configuration.


#### ESP32 with micropython PWM experiments

Based on the code snippet below:
  
```
from machine import Pin, PWM
p25 = Pin(25, Pin.OUT)
motor = PWM(p25, freq=50)
motor.duty(40)
```

> Setting `s.motor.duty(1023)` does not result in a duty cycle of 100%. There is a 20us "gap" in the waveform. 

Gather more information:

consider command `s.motor.duty(dc)`. A table with various values of `dc` and measured (with oscilloscope) ON time was built.

| dc | ON time (us) | ccc |
| --- | --- | --- |
| 0 | 0 | --- |
| 1 | 19,6 | --- |
| 10 | 196 | --- |
| 100 | 1950 | --- |
| 200 | 3900 | --- |
| 500 | 9800 | --- |
| 1000 | 20000-47 | --- |
| 1023 | 20000-19,6 | --- |

*note*: accuracy increases near dc interval extremes because oscilloscope time scale and trigger shift can be adjusted.

*comment*: visually, frequency is 50Hz (period is 20ms). There are no significant variation from a linear response. It may be safe to conclude that *relation between `dc` and measured `ON time` is linear*.

In a trial and error method we get the following `dc` values for target pulse widths

| target pulse width(us) | closest `dc` value | error (us) |
| --- | --- | --- |
| 500 | 26 | 5 (approx. half a division) |
| 1000 | 51 | less than half a small division (small division=20us) |
| 1500 | 77 | less than half a small division (small division=40us) |
| 2000 | 102 or 103 | less than half a small division (small division=40us) |
| 2500 | 128* | less than half a small division (small division=100us) |

128*: values ranging from 127 to 129 have error smaller than half a small division, 128 is visually closer to 2500us.

#### About electric power

Back to SG90 ...

There is a small DC motor inside the plastic body. DC motors may use electric power enough to shut off a computer USB port (its an overload protection). The microcontroller (e.g. Arduino, ESP32,...) will also be shut off, resulting in communication loss. It can be clearly noticed with Micropython.

Servo DC motor is driven by an electronic circuit that implements a transfer function from PWM signals to motor DC voltage (can be considered a translation from PWM to DC voltage). Small angle displacement requires small difference in DC voltage (usually corresponds to small power consumption increase). Large angle displacement requires large difference in DC voltage (usually corresponds to large power consumption increase). 

SG90 axis is connected to its motor axis through some plastic gears (a reduction box).

A correctly powered and operated SG90 draws power to actively mantain its axis in an angle. If the axis is loaded (twisted with an arm or weight), the load is balanced by an increase in power draw. This can cause a computer USB port to shut off.

SG90 may shake continuously. This seems to be about the precision of the electronic driver or the kind of control circuit (may be a PID(?)). It never reaches the target angle *exactly*. The axis pass the target a little on both sides (clockwise,counter-clockwise) and the control circuit "tries to correct it". Consequently the servo shakes.

A large angle displacement, eg. from zero degree to 150 degree may draw a lot of power from USB port. It may cause USB overload and consequent shut off.

A small angle displacement, eg. from zero degree to 5 degree may not be achievable. Because this small displacement (command) is transduced (by the motor driver) in a small voltage change. The voltage change may not be enough to rotate the DC motor axis.

#### Over-rotation protection

One gear has a tooth to its back side. It is and end-of-course lock to avoid damage to the electronic angle sensor (a trimpot). 

### Abnormal conditions

SG90 axis can get stuck. Gears can have burrs. So depending on the axis angle, a random burr may lock the gears. This condition makes DC motor and electronic driver heat continuously (because the axis never reaches the targeted angle). This can also cause a computer USB port to shut off.

#### Recovery

The safest way is to disassemble the servo (unscrew the four screws from the back of the servo) and inspect for burrs, scrobs, cracked gears, ...)

The fast way is to disconnect the servo and (fimly but gently) rotate the axis (in normal conditions it should roll until reach end-of-course). If the axis is stucked there is a chance it unsticks (**warning**: there is also a chance some gear breaks, choice is yours)

## For the curious one

### screws

![](./images/5023774610377780740.jpg)
![](./images/5026204397931179712.jpg)


### Gears and plastic cap removed

![](./images/5023774610377780749.jpg)

### Cracked motor nut

![](./images/5023774610377780746.jpg)

<!--- ### screws removed

![](./images/5026204397931179714.jpg) --->

### Control circuit and DC motor (through the case)

![](./images/5026204397931179715.jpg)

<!---
### Cracked motor nut


![](./images/5026204397931179716.jpg)
![](./images/5026204397931179717.jpg) --->

### Trimpot (in the servo case, to the right)

![](./images/5026204397931179718.jpg)

### Drip some hot melt glue to see the axis rolling

![](./images/5026204397931179751.jpg)
![](./images/5026204397931179773.jpg)

### Axis rolling video

https://www.youtube.com/watch?v=kpjO1ZUUVWM

Explanation to the varying motor rotation speed:
  
Some gears are part of a feedback loop that, in normal conditions, keep the servo turned to a specific angle.

When one removes the gears the feedback does not happen. In the program one can set the target angle to 20 degrees. This makes the motor control circuit to send some voltage to the motor so it rotates. The voltage is proportional to de difference between the target angle and the trimpot angle. If the trimpot angle is near 20 degrees the voltage is small so the motor rotate slowly. If the trimpot angle is much greater than 20 degrees the voltage is large so the motor rotate fast. If the trimpot angle is less than 20 degrees the voltage is "negative" so the motor rotate to the opposite direction.


## References

Servo gets hot at startup: https://forum.arduino.cc/t/servo-gets-hot-at-start-up/282376/23

Servo overheat and jam: https://forum.arduino.cc/t/servos-sg90-overheat-and-jam-really-fast/559423/4

Modify (disassemble) servo: https://www.instructables.com/How-to-Modify-a-Micro-Servo-Motor-SG90-for-Continu/

Other explanation: https://jawhersebai.com/tutorials/how-to-use-the-sg90-servo-motor/

