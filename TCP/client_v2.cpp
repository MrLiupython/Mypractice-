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

int main() {
  int sock;
  /* 创建服务器地址 */
  struct sockaddr_in ser_adr;
  memset(&ser_adr, 0, sizeof(struct sockaddr_in));
  ser_adr.sin_family = AF_INET;
  ser_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
  ser_adr.sin_port = htons(8080);

  /* 创建socket */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  
  /* 连接服务器 */
  if (connect(sock, (struct sockaddr*)&ser_adr, sizeof(ser_adr)) == -1) {
    printf("connect error\n");
    return -1;
  }
  printf("connected \n");

  /* 正常数据包定义 */
  Body body = {"hello world"};
  Header header;
  header.ver = 1;
  header.body_len = sizeof(body);
  header.cmd = 101;
  char sendData1[sizeof(Header)+sizeof(Body)] = {0};
  memcpy(sendData1, &header, sizeof(header));
  memcpy(sendData1+sizeof(header), &body, sizeof(body));

  /* 分包数据定义 */
  Body body2 = {"hello world2"};
  Header header2;
  header2.ver = 2;
  header2.body_len = sizeof(body2);
  header2.cmd = 102;
  char sendData2_1[sizeof(header2)+2] = {0};
  char sendData2_2[sizeof(body2)-2] = {0};
  memcpy(sendData2_1, &header2, sizeof(header2));
  memcpy(sendData2_1+sizeof(header2), &body2, 2);
  memcpy(sendData2_2, (char*)&body2+2, sizeof(body2)-2);
  
  /* 粘包数据定义 */
  Body body3 = {"hello world3"};
  Header header3;
  header3.ver = 3;
  header3.body_len = sizeof(body3);
  header3.cmd = 103;
  
  Body body4 = {"hello world4"};
  Header header4;
  header4.ver = 4;
  header4.body_len = sizeof(body4);
  header4.cmd = 104;
 
  char sendData3[sizeof(header3)+sizeof(header4)+sizeof(body3)+sizeof(body4)] = {0};
  memcpy(sendData3, &header3, sizeof(header3));
  memcpy(sendData3+sizeof(header3), &body3, sizeof(body3));
  memcpy(sendData3+sizeof(header3)+sizeof(body3), &header4, sizeof(header4));
  memcpy(sendData3+sizeof(header3)+sizeof(body3)+sizeof(header4), &body4, sizeof(body4));

  /* 正常测试 */
  send(sock, sendData1, sizeof(sendData1), 0);
  printf("正常测试结束。。\n");
  sleep(3);
  
  /* 分包测试 */
  send(sock, sendData2_1, sizeof(sendData2_1), 0);
  printf("分包1测试结束。。\n");
  sleep(1);
  send(sock, sendData2_2, sizeof(sendData2_2), 0);
  printf("分包2测试结束。。\n");
  sleep(3);

  /* 粘包测试 */
  send(sock, sendData3, sizeof(sendData3), 0);
  printf("粘包测试结束。。\n");
  sleep(3);

  printf("关闭连接");
  close(sock);
}
