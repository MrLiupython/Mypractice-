import socket
import threading
target_host = "localhost"
target_port = 49289
def handle_send(client_socket):
    while True:
        say = input()
        client_socket.send(str.encode(say))
def handle_recv(client_socket):
    while True:
        response = client_socket.recv(1024)
        print(bytes.decode(response))
def handle_client(client_socket):
    h1 = threading.Thread(target=handle_recv,args=(client_socket,))
    h1.start()
    handle_send(client_socket)
def main():
    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect((target_host,target_port))
    client.send(bytes("Have one join!",encoding="utf-8"))
    while True:
        handle_client(client)
        client.close()
if __name__ == "__main__":
    main()
