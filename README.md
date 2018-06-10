[![Build Status](https://travis-ci.org/GTAeberhard/pwm_motor_control.svg?branch=master)](https://travis-ci.org/GTAeberhard/pwm_motor_control)

# PWM Motor Control

## Introduction

In this repository you will find some basic code for controlling typical PWM
motors with popular embedded hardware.  Initially it will be implemented
for the [Raspberry Pi](https://www.raspberrypi.org/) to drive motors connected to
an [L239D](http://www.ti.com/lit/ds/symlink/l293.pdf) Half-H driver.  Hopefully the
design of the code will make it easy to also support other devices.

## Lego Power Functions

The main motivation for this project is to control the
[LEGO Power Functions](https://www.lego.com/powerfunctions/) 
[DC motor](https://www.lego.com/powerfunctions/products/xl-motor-8882) and
[servo motor](https://www.lego.com/powerfunctions/products/servo-motor-88004).

Below are some useful links that helped me get everything setup:
* [Take Control Over Lego Power Functions](https://www.hackster.io/Notthemarsian/take-control-over-lego-power-functions)
* [Philo's LEGO Technical Information](http://www.philohome.com/tech.htm)

