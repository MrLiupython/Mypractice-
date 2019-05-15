#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

/* 包头 */
typedef struct header {
  int ver;
  int body_len;
  int cmd;
}Header;

/* 包体 */
typedef struct body {
  char words[120];
}Body;

void dataHandle(Header* headPack, Body* body, int & sn) {
  sn++;
  printf("第%d个数据包\n", sn);
  printf("ver: %d, body_len: %d, cmd: %d\n", headPack->ver, \
    headPack->body_len, headPack->cmd);
  printf("%s\n", body->words);
  printf("\n");
}

int main() {
  int ser_sock, cli_sock;
  int sn = 0;
  
  /* 数据读缓存 */
  char r_buf[1024] = {0};
  int r_len = 1024;
  /* 多余数据缓存 */
  char data_buffer[2048] = {0};
  int d_len = 2048;
  int use_len = 0;

  /* 本地地址 */
  struct sockaddr_in ser_adr;
  memset(&ser_adr, 0, sizeof(ser_adr));
  ser_adr.sin_family = AF_INET;
  ser_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_adr.sin_port = htons(8080);
  
  /* 客户socket */
  socklen_t cli_len;
  struct sockaddr_in cli_adr;
  memset(&cli_adr, 0, sizeof(cli_adr));

  /* 创建插口 */
  ser_sock = socket(PF_INET, SOCK_STREAM, 0);
  
  /* 插口绑定插口 */
  if (bind(ser_sock, (struct sockaddr*)&ser_adr, sizeof(ser_adr)) == -1)
    printf("bind error");
  
  /* 监听 */
  listen(ser_sock, 1);
  
  cli_sock = accept(ser_sock, (struct sockaddr*)&cli_adr, &cli_len);
  while (1) {
    printf("Connected by %d\n", cli_sock);
    while (1) {
      int r = recv(cli_sock, r_buf, r_len, 0);
      if (r) {
        /* 数据进缓存 */
        memcpy(data_buffer+use_len, r_buf, r);
        use_len = use_len + r;
        while (1) {
          if (use_len < sizeof(Header)) {
            printf("数据包 （%d Byte) 小于消息头部，跳出小循环.\n", use_len);
            break;
           }
           /* 读取包头 */
           Header headPack;
           memcpy(&headPack, data_buffer, sizeof(Header));
           
           /* 分包处理 */
           if (use_len < sizeof(Header) + sizeof(Body)) {
             printf("数据包 （%d Byte) 不完整（总共%dByte),跳出小循环。\n", use_len, sizeof(Header)+sizeof(Body));
             break;
           }

           /* 数据处理 */
           Body body;
           memcpy(&body, data_buffer+sizeof(headPack), sizeof(body));
           
           dataHandle(&headPack, &body, sn);
           /*
           sn++;
           printf("第%d个数据包\n", sn);
           printf("ver: %d, body_len: %d, cmd: %d\n", headPack.ver, \
             headPack.body_len, headPack.cmd);
           printf("%s\n", body.words);
           printf("\n");
           */
           /* 粘包处理 */
           use_len = use_len - sizeof(Header) - sizeof(Body);
           memmove(data_buffer, data_buffer+sizeof(Header)+sizeof(Body), use_len);
           memset(data_buffer+use_len, 0, d_len - use_len);
        }
      }
    }
  }
}
