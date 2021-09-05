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
    
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    if(ret == -1)
        perror("Fail to bind CAN socket: -");
        
    return sock;
}

int main(void)
{
    struct can_frame frame;
    int sock = InitCanInterface("slcan0");

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

    char str[10];

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

    std::cout<<"Motor Velocity Read\n";
    frame.can_id = 0x381|CAN_RTR_FLAG;
    write(sock,&frame,sizeof(can_frame));

    sleep(10);

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