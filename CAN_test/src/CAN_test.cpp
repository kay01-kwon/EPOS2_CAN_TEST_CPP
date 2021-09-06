#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>

struct sockaddr_can addr;

int InitCanInterface(const char *ifname)
{
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(sock == -1){
        printf("Fail to create CAN socket for %s - %m\n",ifname);
        return -1;
    }
    printf("Success to create CAN socket for %s \n",ifname);

    struct  ifreq ifr;
    strcpy(ifr.ifr_name, ifname);
    int ret = ioctl(sock, SIOCGIFINDEX, &ifr);

    if(ret == -1){
        perror("Fail to get CAN interface index -");
        return -1;
    }
    printf("Success to get CAN interface index: %d\n",ifr.ifr_ifindex);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    if(ret == -1)
        perror("Fail to bind CAN socket: -");
        
    return sock;
}

int HexarrayToInt(unsigned char *buffer,int length)
{
    int hextoint = 0;
    int data = 0;
    for(int i = 0; i < length; i++){
        hextoint += (buffer[i] << 8*i);
        data = (int) buffer[i];
        //printf("Index: %d \t Data: %02x \n",i,buffer[i]);
    }

    return hextoint;
}

int main(void)
{
    struct can_frame frame;
    struct canfd_frame frame_fd;

    struct iovec iov;
    struct msghdr can_msg;
    char ctrlmsg[CMSG_SPACE(sizeof(struct timeval) + 3*sizeof(struct timespec) + sizeof(__u32))];
    struct canfd_frame frame_get;

    int sock = InitCanInterface("slcan0");
    int nbytes = 0;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    if(sock < 0)
        return -1;

    std::cout<<"Network Manegerment Initialization \n";

    frame.can_id = 0x000;
    frame.can_dlc = 2;
    frame.data[0] = 0x81;
    frame.data[1] = 0x00;

    write(sock,&frame,sizeof(can_frame));
    sleep(1);

    std::cout<<"Remote Mode\n";
    frame.can_id = 0x000;
    frame.can_dlc = 2;
    frame.data[0] = 0x01;
    frame.data[1] = 0x00;
    write(sock,&frame,sizeof(can_frame));
    sleep(1);


    //PDO 
    std::cout<<"Velocity Mode initiate\n";   
    frame.can_id = 0x301;
    frame.can_dlc = 3;
    frame.data[0] = 0x00;
    frame.data[1] = 0x00;
    frame.data[2] = 0x03;
    write(sock,&frame,sizeof(can_frame));

    sleep(1);

    std::cout<<"Controlword shutdown\n";   
    frame.can_id = 0x201;
    frame.can_dlc = 2;
    frame.data[0] = 0x06;
    frame.data[1] = 0x00;
    write(sock,&frame,sizeof(can_frame));

    sleep(1);

    std::cout<<"Controlword Enabled\n";   
    frame.can_id = 0x201;
    frame.can_dlc = 2;
    frame.data[0] = 0x0F;
    frame.data[1] = 0x00;
    write(sock,&frame,sizeof(can_frame));

    sleep(1);

    std::cout<<"Motor Run\n";   

    frame.can_id = 0x401;
    frame.can_dlc = 6;
    frame.data[0] = 0x0F;
    frame.data[1] = 0x00;
    frame.data[2] = 0x10;
    frame.data[3] = 0x10;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    write(sock,&frame,sizeof(can_frame));
    
    sleep(1);

    std::cout<<"Motor Velocity Read: \t";
    frame.can_id = 0x381|CAN_RTR_FLAG;
    write(sock,&frame,sizeof(can_frame));

    iov.iov_base = &frame_get;
    can_msg.msg_name = & addr;
    can_msg.msg_iov = &iov;
    can_msg.msg_iovlen = 1;
    can_msg.msg_control = &ctrlmsg;

    iov.iov_len = sizeof(frame_get);
    can_msg.msg_namelen = sizeof(addr);
    can_msg.msg_controllen = sizeof(ctrlmsg);
    can_msg.msg_flags = 0;
    sleep(1);

    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&tv,sizeof tv);

    recvmsg(sock,&can_msg,0);

    nbytes = recvmsg(sock,&can_msg,0);
    int data = HexarrayToInt(frame_get.data,4);
    std::cout<<data<<std::endl;

    sleep(5);

    std::cout<<"Stop Motor \n";
    frame.can_id = 0x401;
    frame.can_dlc = 6;
    frame.data[0] = 0x0F;
    frame.data[1] = 0x00;
    frame.data[2] = 0x00;
    frame.data[3] = 0x00;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    write(sock,&frame,sizeof(can_frame));

    sleep(2);

    std::cout<<"Reset Remote Mode \n";
    frame.can_id = 0x000;
    frame.can_dlc = 2;
    frame.data[0] = 0x81;
    frame.data[1] = 0x00;

    write(sock,&frame,sizeof(can_frame));
    sleep(1);

    std::cout<<"Stop Remote Mode\n";
    frame.can_id = 0x000;
    frame.can_dlc = 2;
    frame.data[0] = 0x02;
    frame.data[1] = 0x00;
    write(sock,&frame,sizeof(can_frame));
    sleep(1);
}