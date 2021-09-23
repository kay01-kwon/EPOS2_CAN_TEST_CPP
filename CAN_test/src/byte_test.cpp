#include <iostream>
#include <sstream>
#include <stdio.h>
#include <linux/types.h>
#include <linux/socket.h>
#include <bitset>
#include <vector>

typedef __u32 fake_can_id_t;

struct fake_can_frame{
    fake_can_id_t fake_can_id;
    __u8 fake_can_dlc;
    __u8 data[8];
};

int main()
{
    fake_can_frame fake_frame;

    fake_frame.data[0] = 0x0f;
    fake_frame.data[1] = 0x00;
    int input_data = 6000;

    std::vector<std::bitset<8> > data_byte[4];

    for(int i = 0; i < 4; i++){
        data_byte->push_back((input_data >> 8*i));
        fake_frame.data[i+2] = unsigned(data_byte->at(i).to_ulong());
    }


    std::cout<<"Data: \t";
    std::cout<<input_data<<std::endl;

    std::cout<<"Data Inserted"<<std::endl;
    std::cout<<"The first byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[2])<<std::endl;
    std::cout<<"The second byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[3])<<std::endl;
    std::cout<<"The third byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[4])<<std::endl;
    std::cout<<"The fourth byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[5])<<std::endl;

    for (int i = 2; i < 6; i++)
        printf("Index : %d \t Data : %02x \n",i,fake_frame.data[i]);
}