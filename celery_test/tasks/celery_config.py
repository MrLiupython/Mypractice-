BROKER_URL = 'redis://127.0.0.1:6380/11'
CELERY_RESULT_BACKEND = 'redis://127.0.0.1:6380/10'
CELERY_TASK_SERIALIZER = 'json'
CELERY_RESULT_SERIALIZER = 'json'
CELERY_TASK_RESULT_EXPIRES = 60 * 60 * 24
CELERY_ACCEPT_CONTENT = ['json']

CELERYBEAT_SCHEDULE = {
    'send': {
        'task': 'tasks.celery_tasks.send_worker',
        'schedule': 5,
        'options': {'queue': 'beat_worker'}
    }
}
        

CELERY_ROUTES = {
    'tasks.celery_tasks.worker_1': {
        'queue': 'worker1',
        # 'routing_key': 'tasks.worker_1'
        }
    }

