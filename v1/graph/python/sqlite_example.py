import sqlite3

# 1. Create connection object

conn = sqlite3.connect(":memory:")

# 2. Create cursor object instance

c = conn.cursor()

#3. Create a table
#a. execute method - perform SQL commands
c.execute('''CREATE TABLE IF NOT EXISTS foo
            (date text, trans text, symbol text, qty real, price real)''')

c.execute("INSERT INTO foo VALUES ('2006-01-05','BUY','RHAT',100,35.14)")
#4. Save the changes
conn.commit()

# 5. Close the connection
conn.close()
