#!/bin/bash
g++ control_GPIO.cpp -o control_GPIO
config-pin p9.12 gpio
config-pin p8.16 gpio_pu
