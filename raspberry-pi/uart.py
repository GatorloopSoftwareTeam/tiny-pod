#!/usr/bin/env python   
      
import time
import serial

START_BYTE = b'\x17'
STOP_BYTE = b'\x30'
ESCAPE_BYTE = b'\x7D'

ser = serial.Serial(            
    port='/dev/serial0',
    baudrate = 115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

def send_packet(packets):
    #Send start condition
    ser.write(START_BYTE)
    
    for packet in packets:
        
        #Check if escape byte is needed
        if packet == START_BYTE or packet == STOP_BYTE or packet == ESCAPE_BYTE:
            ser.write(ESCAPE_BYTE)
        
        #Send data
        ser.write(packet)
    
    #Send stop condition
    ser.write(STOP_BYTE)


def read_packet():
    data = []
    started = False
    escape = False
    
    while 1:
        read = ser.read(1)
        start_condition = read == START_BYTE
        end_condition = read == STOP_BYTE
        escape_condition = read == ESCAPE_BYTE
        
        if not escape:
            #Start condition
            if start_condition:
                started = True
                continue
            
            #End condition
            if end_condition:
                break
            
            #Break condition
            if escape_condition:
                escape = True
                continue
        else:
            escape = False
        
        if started:
            data.append(read)
        
        
    
    return data

