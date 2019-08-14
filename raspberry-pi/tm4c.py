import uart
import threading
import time

#Callback definintions


#temp_callback(temp)
# temp - temperature in celsius

#accel_callback(x, y, z)
#
# x - x accleration vector
# y - y accleration vector
# z - z accleration vector
#
# data is in m/s

#gyro_callback(x, y z)
#
# x - x gyro vector
# y - y gyro vector
# z - z gyro vector
#
# data is in degrees per second

#volt_callback(volts) 
# volts - DC voltage

START_CONDITION = b'\x3F'
AWK = b'\x2D'
TEMP_ADDR = b'\x01'
ACCEL_ADDR = b'\x02'
GYRO_ADDR = b'\x03'
VOLT_ADDR = b'\x04'

def init(temp_callback, accel_callback, gyro_callback, volt_callback):
    #init the serial
    uart.send_packet([START_CONDITION])
    
    #Wait for awknowledge from tm4c
    awk = True
    while not awk:
        data = uart.read_packet()
        
        if data[0] == AWK:
            awk = True
    
    data_thread = threading.Thread(target=read_data, args=(temp_callback,accel_callback,gyro_callback,volt_callback))
    data_thread.start()


def format_data(packet, index):
    return (int(ord(packet[index + 1])) << 8) | int(ord(packet[index]))



def read_data(temp_callback, accel_callback, gyro_callback, volt_callback):
    while 1:
        packet = uart.read_packet()
        if len(packet) >= 3:
            addr = packet[0]
            
            if addr == TEMP_ADDR:
                temp = format_data(packet, 1)
                temp_callback(temp)
            
            elif addr == ACCEL_ADDR:
                x = format_data(packet, 1)
                y = format_data(packet, 3)
                z = format_data(packet, 5)
                accel_callback(x, y, z)
            
            elif addr == GYRO_ADDR:
                x = format_data(packet, 1)
                y = format_data(packet, 3)
                z = format_data(packet, 5)
                gyro_callback(x, y, z)
            
            elif addr == VOLT_ADDR:
                volts = format_data(packet, 1)
                volt_callback(volts)


def temp(num):
    print("temp")
    print(num)
    return num

def accel(x, y, z):
    print("accel")
    print(x)
    print(y)
    print(z)
    return x

def gyro(x, y, z):
    print("gyro")
    print(x)
    print(y)
    print(z)
    return x

def volt(num):
    print("volt")
    print(num)
    return num

if __name__ == "__main__":
    init(temp, accel, gyro, volt)
    
