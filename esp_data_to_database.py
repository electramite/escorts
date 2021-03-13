import socket
import mysql.connector
import time


mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="nnn",
  database="CBM"
)
mycursor = mydb.cursor()
sql = "INSERT INTO Sensor_data (data, time) VALUES (%s, %s)"
 
s = socket.socket()         
s.bind(('0.0.0.0', 8020 ))
s.listen(0)                 
 
while True:
 
    client, addr = s.accept()
 
    while True:
        content = client.recv(32)
 
        if len(content) ==0:
           break 
        else:
      
            content = content.decode("utf-8")
            ti = time.gmtime()
            val = (f"{content}", f"{time.asctime(ti)}")
            mycursor.execute(sql, val)
            mydb.commit()
            print(mycursor.rowcount, "record inserted.")
    client.close()
