def to_str(date):#bytes字节码 str(Unicode)字符串编码
    if isinstance(date,str):
        return date
    else:
        return date.decode('utf-8')
def to_bytes(date):
    if isinstance(date,bytes):
        return date
    else:
        return str.encode(date)