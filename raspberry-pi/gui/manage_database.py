import sqlite3 as lite
import sys, datetime

# This file contains insert and get functions for sensors

# Insert values into Tables

def insertTableTemperature(t):
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("INSERT INTO TEMPERATURE VALUES( (?), (?))", (datetime.datetime.now(), t))
    conn.commit()
    conn.close()

def insertTableAccelaration(x, y, z):
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("INSERT INTO ACCELARATION VALUES( (?), (?), (?), (?))", (datetime.datetime.now(), x, y, z))
    conn.commit()
    conn.close()

def insertTableGyroscope(x, y, z):
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("INSERT INTO GYROSCOPE VALUES( (?), (?), (?), (?))", (datetime.datetime.now(), x, y, z))
    conn.commit()
    conn.close()

def insertTableVoltage(v):
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("INSERT INTO VOLTAGE VALUES( (?), (?))", (datetime.datetime.now(), v))
    conn.commit()
    conn.close()

# def insertTableCurrent(i):
#     conn = lite.connect('SensorData.db')
#     curr=conn.cursor()
#     curr.execute("INSERT INTO CURRENT VALUES( (?), (?))", (datetime.datetime.now(), i))
#     conn.commit()


# Retrieve values from the tables

def getTableTemperature():
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("SELECT * FROM TEMPERATURE ORDER BY date DESC LIMIT 1")
    return curr.fetchall()

def getTableAccelaration():
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("SELECT * FROM ACCELARATION ORDER BY date DESC LIMIT 1")
    return curr.fetchall()

def getTableGyroscope():
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("SELECT * FROM GYROSCOPE ORDER BY date DESC LIMIT 1")
    return curr.fetchall()

def getTableVoltage():
    conn = lite.connect('SensorData.db')
    curr=conn.cursor()
    curr.execute("SELECT * FROM VOLTAGE ORDER BY date DESC LIMIT 1")
    return curr.fetchall()

# def getTableCurrent():
#     conn = lite.connect('SensorData.db')
#     curr=conn.cursor()
#     curr.execute("SELECT * FROM CURRENT ORDER BY date DESC LIMIT 1")
#     return curr.fetchall()
