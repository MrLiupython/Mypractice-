import pymysql

conn = pymysql.connect('localhost','root','****','testp')
cur = conn.cursor()

def addUser(username,password):
    sql = 'INSERT INTO testp.user (name,password) VALUES ("%s","%s");' % (username,password)
    cur.execute(sql)
    conn.commit()
    # conn.close()
def isUser(username,password):
    sql = 'SELECT * FROM testp.user WHERE (name="%s" AND password="%s");' % (username,password)
    print(sql)
    cur.execute(sql)
    result = cur.fetchall()
    if len(result) == 0:
        return False
    else:
        return True
def isHave(username):
    sql = 'SELECT * FROM testp.user WHERE (name="%s");'% username
    cur.execute(sql)
    result = cur.fetchall()
    if len(result) == 0:
        return False
    else:
        return True
def saveContext(title,context,type):
    sql = 'INSERT INTO testp.context (title,context,type) VALUES ("%s","%s","%s");' % (title,context,type)
    cur.execute(sql)
    conn.commit()
#    conn.close()
def putContext():
    sql = 'SELECT * FROM testp.context;'
    cur.execute(sql)
    result = cur.fetchall()
    return result
