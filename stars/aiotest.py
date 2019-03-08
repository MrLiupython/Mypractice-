import asyncio
from aiohttp import ClientSession
from queue import Queue
import time
import requests
class Crawler:
    def __init__(self):
        self.tasks = Queue()
        self.result = Queue()
    def add_task(self, url=None, url_list=None):
        if url:
            self.tasks.put(url)
        if url_list:
            for i in url_list:
                self.tasks.put(i)
    async def fetch(self):
        if not self.tasks.empty():
            #print(self.tasks.qsize())
            url = self.tasks.get()
            async with ClientSession() as session:
                async with session.get(url) as resp:
                    self.result.put(await resp.text())
    def task_num(self):
        return self.tasks.qsize()
    def __iter__(self):
        while not self.result.empty():
            yield self.result.get()


if __name__ == "__main__":
    start = time.time()
    loop = asyncio.get_event_loop()
    todo_url = []
    for i in range(4):
        todo_url.append('http://httpbin.org/anything?hello={}'.format(i))
    crawl = Crawler()
    crawl.add_task(url_list=todo_url)
    num = crawl.task_num()
    tasks = [ crawl.fetch() for i in range(num)]
    loop.run_until_complete(asyncio.gather(*tasks))
    loop.close()
    #print('result: ')
    for i in crawl:
        print(i)
    print('over(aiohttp)-{}'.format(time.time() - start))
    start = time.time()
    for i in todo_url:
        r = requests.get(i)
        print(r.text)
    print('over(requests)-{}'.format(time.time() - start))