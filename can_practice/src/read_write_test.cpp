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

#include <signal.h>

using std::cout;

int InitCanInterface(const char *ifname)
{
    /* Create CAN socket */
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(sock == -1)
    {
        cout<<"Fail to get can interface index"<<"\n";
        return -1;
    }
    cout<<"Success to get can socket for "<<ifname<<"\n";

    /* Get CAN interface index */ 
    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifname);
    int ret =ioctl(sock,SIOCGIFINDEX, &ifr);

    if(ret == -1){
        cout<<"Fail to get can interface index \n";
        return -1;
    }
    cout<<"Success to get can interface index"<<ifr.ifr_ifindex<<"\n";

    /* Bind CAN socket */
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(sock, (struct sockaddr*)& addr, sizeof(addr));

    if(ret == -1){
        cout<<"Fail to bind can socket \n";
        return -1;
    }
    cout<<"Success to bind can socket \n";

    return sock;
}

int TransmitCanFrame(const int sock, const uint32_t id, 
const uint8_t* data, const size_t data_len)
{
    struct can_frame frame;
    frame.can_id = id;
    memcpy(frame.data, data, data_len);
    frame.can_dlc = data_len;

    int tx_bytes = write(sock, &frame, sizeof(frame));
    if(tx_bytes == -1)
    {
        cout<<"Fail to transmit can frame ";
        return -1;
    }
    return 0;
}

int ReceiveCanFrame(const int sock)
{
    struct can_frame frame;
    int rx_bytes = read(sock, &frame, sizeof(frame));
    if(rx_bytes < 0)
    {
        cout<<"Fail to receive can frame \n";
        return -1;
    }else if(rx_bytes < (int) sizeof(struct can_frame))
    {
        cout<<"Incomplete can frame is received - rx bytes: "<<rx_bytes<<"\n";
        return -1;
    }

    cout<<std::hex;

    cout<<" CAN id: "<<frame.can_id<<"\t";
    for(int i = 0; i < 4;i++)
        cout<<"CAN data "<<(i+1)<<" : "<<(unsigned)frame.data[i]<<"  ";
    cout<<"\n";

    return 0;
}

bool m_break;

void OnSignal(int sig)
{
    signal(sig, SIG_IGN);
    cout<<"Break\n";
    m_break = true;
}

int main()
{
    int sock = InitCanInterface("can0");

    signal(SIGINT, OnSignal);

    uint32_t CAN_ID[4] = {0x101, 0x102, 0x103, 0x104};
    uint8_t data[8];
    for(int i = 0; i < 8; i++)
        data[i] = i;

    while(!m_break){
        for(int i = 0; i < 4; i++){
            TransmitCanFrame(sock, CAN_ID[i], data, 8);
            //data[i]++;
        }
        ReceiveCanFrame(sock);
    }

    return 0;
}