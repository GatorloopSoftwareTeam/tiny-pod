import sqlite3 as lite
import sys, datetime

# This file creates the schema for the database

conn = lite.connect('SensorData.db')
cur=conn.cursor()

def createTableTemperature():
    cur.execute("DROP TABLE IF EXISTS TEMPERATURE")
    cur.execute("CREATE TABLE TEMPERATURE(date DATETIME, temp NUMERIC)")
    cur.execute("INSERT INTO TEMPERATURE VALUES( (?), (?))", (datetime.datetime.now(), 0))
    conn.commit()

def createTableAccelaration():
    cur.execute("DROP TABLE IF EXISTS ACCELARATION")
    cur.execute("CREATE TABLE ACCELARATION(date DATETIME, x NUMERIC, y NUMERIC, z NUMERIC)")
    cur.execute("INSERT INTO ACCELARATION VALUES( (?), (?), (?), (?))", (datetime.datetime.now(), 0, 0, 0))
    conn.commit()

def createTableGyroscope():
    cur.execute("DROP TABLE IF EXISTS GYROSCOPE")
    cur.execute("CREATE TABLE GYROSCOPE(date DATETIME, x NUMERIC, y NUMERIC, z NUMERIC)")
    cur.execute("INSERT INTO GYROSCOPE VALUES( (?), (?), (?), (?))", (datetime.datetime.now(), 0, 0, 0))
    conn.commit()

def createTableVoltage():
    cur.execute("DROP TABLE IF EXISTS VOLTAGE")
    cur.execute("CREATE TABLE VOLTAGE(date DATETIME, volt NUMERIC)")
    cur.execute("INSERT INTO VOLTAGE VALUES( (?), (?))", (datetime.datetime.now(), 0))
    conn.commit()

# def createTableCurrent():
#     cur.execute("DROP TABLE IF EXISTS CURRENT")
#     cur.execute("CREATE TABLE CURRENT(date DATETIME, curr NUMERIC)")
#     cur.execute("INSERT INTO CURRENT VALUES( (?), (?))", (datetime.datetime.now(), 0))
#     conn.commit()

createTableAccelaration()
createTableGyroscope()
createTableVoltage()
createTableTemperature()

conn.close()
