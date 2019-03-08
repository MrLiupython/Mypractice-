import aiohttp
import asyncio
import sys
import time
async def aio2():
    async with aiohttp.ClientSession() as session:
        async with session.options('http://httpbin.org/get')as resp:
            print('aio2-GET: ',resp.status)
            print('aio2: ' + await resp.text())
        async with session.patch('http://httpbin.org/patch', data=b'data') as resp:
            print('aio2-PATCH: ',resp.status)
            print('aio2: ' + await resp.text())

async def aio1():
    async with aiohttp.ClientSession() as session:
        async with session.get('http://httpbin.org/get') as resp:
            print('aio1-GET: ',resp.status)
            print('aio1: ' + await resp.text())
        async with session.post('http://httpbin.org/post', data={'data': 'hello world'}) as resp:
            print('aio1-POST: ', resp.status)
            print('aio1: ' + await resp.text())
try:
    loop = asyncio.get_event_loop()
    task = [aio1(), aio2()]
    loop.run_until_complete(asyncio.wait(task))
    aiohttp.sleep(2)
    print('ss')
finally:
    loop.stop()
    print('Bye')
    sys.exit()
