# -*- coding: utf-8 -*-
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr
import smtplib

FROM_ADDR = ''
TO_ADDR = ''
SMTP_SERVER = ''
PASSWD = ''
SMTP_PORT = ''

def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((
        Header(name, 'utf-8').encode(),
        addr.decode('utf-8') if isinstance(addr, bytes) else addr))
        
        
def send_email(message):
    try:
        msg = MIMEText(message, 'plain', 'utf-8')
        msg['From'] = _format_addr(u'test python <{}>'.format(FROM_ADDR))
        msg['To'] = _format_addr(u'管理员 <{}>'.format(TO_ADDR))
        msg['Subject'] = Header(u'来自python的问候...', 'utf-8').encode()

        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.set_debuglevel(1)
        server.login(FROM_ADDR, PASSWD)
        server.sendmail(FROM_ADDR, [TO_ADDR], msg.as_string())
        server.quit()
    except Exception as e:
        print(str(e))
        return False
    return True

if __name__ == "__main__":
    send_email("test python")
