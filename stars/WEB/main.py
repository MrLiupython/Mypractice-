from flask import Flask,flash,request,render_template,redirect,url_for
from models import *

app = Flask(__name__)
app.secret_key = 'dhlsafjdl23lad'
name = 'tourists'

@app.route('/')
def i():
    return redirect('login')

@app.route('/login',methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        u = User2(username,password)
        if u.isHave():
            global name
            name = username
            return redirect(url_for('entry'))
        else:
            flash("username or password is wrong")
            return render_template('index.html')
    return render_template('index.html')

@app.route('/register',methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        u = User2(username,password)
        if u.isSame():
            flash("The name hsa used")
            return render_template('index2.html')
        else:
            u.add()
            return redirect(url_for('login'))
    return render_template('index2.html')

@app.route('/show',methods=['GET','POST'])
def show():
    c = get_content()
    if request.method == 'POST':
        title = request.form['title']
        content = request.form['content']
        e = Entry(title,content,name)
        e.add()
        return render_template('entry.html',entrys=c,name=name)
    return render_template('entry.html',entrys=c,name=name)

@app.errorhandler(404)
def not_found(e):
    return render_template('404.html')

if __name__ == "__main__":
    app.run(port=8080)
