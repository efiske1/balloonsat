import time
import board
import math
import adafruit_icm20x
from datetime import datetime
import numpy as np
from numpy import mean
i2c = board.I2C()  # uses board.SCL and board.SDA
icm = adafruit_icm20x.ICM20948(i2c)
prev_acc = 0

while True:
    ##measure average acceleraction (10 polls) 
    accel_arr = (icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,
           icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration,icm.acceleration)
    ##calculate average accel
    def avg(accel_arr):
        result = tuple(map(lambda x: sum(x) / float(len(x)), zip(*accel_arr)))
        return result
    acc=avg(accel_arr)
    
    #calculate accel magnitude
    acc_mag = math.sqrt(acc[0]**2+acc[1]**2+acc[2]**2)
    
    #record acceleration values if changing from rest
    if (abs(acc_mag - prev_acc) > .05):
        print("old avg = %.2f" % prev_acc)
        print("Acceleration: X:%.2f, Y: %.2f, Z: %.2f m/s^2" % (acc[0], acc[1], acc[2]))
        print("avg: %.2f" % acc_mag)
        print("Diff: %.2f" % abs(acc_mag - prev_acc))
        print("Gyro X:%.2f, Y: %.2f, Z: %.2f rads/s" % (icm.gyro))
        print("Magnetometer X:%.2f, Y: %.2f, Z: %.2f uT" % (icm.magnetic))
        print("")
        
    #poll every .1s
    time.sleep(.1)
    #set up previous accel for next loop
    prev_acc = acc_mag
        

## icm.acceleration
