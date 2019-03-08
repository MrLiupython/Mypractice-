from celery import Celery

app = Celery('tasks', include=['tasks.celery_tasks'])
app.config_from_object('tasks.celery_config')

if __name__ == "__main__":
    app.start()
