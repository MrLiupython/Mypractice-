import socket
import threading
bind_ip = "localhost"
bind_port = 49289
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind((bind_ip,bind_port))
server.listen(5)
print("[*] Listening on %s:%d" % (bind_ip,bind_port))
def handle_send(client_socket):
    while True:
        say = input()
        client_socket.send(str.encode(say))
def handle_recv(client_socket):
    while True:
        request = client_socket.recv(1024)
        print(bytes.decode(request))
def main():
    while True:
        client,addr = server.accept()
        client.send(str.encode("Welcome to MyChat!"))
        print("[*] Accepted connection from %s:%d" % (addr[0],addr[1]))
        client_handle= threading.Thread(target=handle_recv,args=(client,))
        client_handle.start()
        handle_send(client)
        client.close()
if __name__ == "__main__":
    main()
