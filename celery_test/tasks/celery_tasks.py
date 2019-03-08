from tasks.celery_app import app

@app.task
def add(x, y):
    return x + y

@app.task
def worker_1():
    print('worker_1')

@app.task
def send_worker():
    client = app.connection().channel().client
    l = client.llen('celery')
    length = client.llen('worker1')
    length2 = client.llen('worker2')
    print('celery: {}, worker1: {}, worker2: {}\nsend tasks'.format(l, length, length2))
    res1 = worker_1.apply_async()
    res2 = worker_1.apply_async(queue='worker2')
    length = client.llen('worker1')
    length2 = client.llen('worker2')
    print('celery: {}, worker1: {}, worker2: {}\nend'.format(l, length, length2))