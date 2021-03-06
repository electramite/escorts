import socket
import time
import re
import mysql.connector

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="@Godown69", # db password
  database="escorts" # db name
)
 
s = socket.socket()         
 
s.bind(('0.0.0.0', 4579))
s.listen(5) 
def insert_data(temp, aX, aY, aZ, pitch, roll, yaw, time):
    mycursor = mydb.cursor()
    sql = "INSERT INTO sensor_data (temp, aX, aY, aZ, pitch, roll, yaw, time) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"
    val = (temp, aX, aY, aZ, yaw, pitch, roll, time)
    mycursor.execute(sql, val)
    mydb.commit()
    print(mycursor.rowcount, "record inserted.")

while True:
    c, addr = s.accept()   # receiving sensor data   
    d1 = c.recv(1024).decode('utf-8') 
    D1 = re.findall(r"[-+]?\d*\.\d+|\d+", d1) # extracting readings from string and storing them in a list
    ti = time.gmtime() # current time
    insert_data(D1[0], D1[1], D1[2], D1[3], D1[4], D1[5], D1[6], time.asctime(ti)) # inserting them into db
    print(D1)
