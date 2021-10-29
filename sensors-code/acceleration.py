import time
import board
import adafruit_icm20x
from datetime import datetime
import numpy as np
from numpy import mean
i2c = board.I2C()  # uses board.SCL and board.SDA
icm = adafruit_icm20x.ICM20948(i2c)
now = datetime.now()
arr = (icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration)
def avg(arr):
    result=[sum(x)/len(x) for x in zip(*arr)]
    return result
a=avg(arr)

if (icm.acceleration != a):
    while True:
       
        print("Acceleration: X:%.2f, Y: %.2f, Z: %.2f m/s^2" % (icm.acceleration))
        print("Gyro X:%.2f, Y: %.2f, Z: %.2f rads/s" % (icm.gyro))
        print("Magnetometer X:%.2f, Y: %.2f, Z: %.2f uT" % (icm.magnetic))
        print("")
        time.sleep(3)

