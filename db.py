import mysql.connector
mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="*******",
  database="CBM"
)
mycursor = mydb.cursor()
#insert
sql = "INSERT INTO Sensor_data (data, time) VALUES (%s, %s)"


val = ("273.00", "12:36")
mycursor.execute(sql, val)
mydb.commit()
print(mycursor.rowcount, "record inserted.")

mycursor.execute("SELECT * FROM Sensor_data")
myresult = mycursor.fetchall()
for x in myresult:
  print(x)
