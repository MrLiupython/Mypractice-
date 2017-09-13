#It depend on Window's command(rar).So make sure your rar command can run.
import os
import sys
import time

source = input('From:\n')
if not os.path.exists(source):
    print('Not Found->',source)
    sys.exit()
    time.sleep(3)
    sys.exit()

target_dir = input('To:\n')
if not os.path.exists(target_dir):
    os.mkdir(target_dir)
    print('Created directory:',target_dir)

today = target_dir + os.sep + time.strftime('%Y%m%d')
if not os.path.exists(today):
    os.mkdir(today)
    print('Created directory:',today)
now = today + os.sep + time.strftime('%H%M%S') + '.rar'

cmd_command = 'rar a {} {}'.format(now,source)
print('Cmd command:',cmd_command)
print('Running----')
if os.system(cmd_command) == 0:
    print('Backup to :',now)
    print('Successfully!')
    time.sleep(3)
else:
    print('Backup failed\nBye!')
    time.sleep(3)
