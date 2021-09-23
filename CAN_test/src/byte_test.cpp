#include <iostream>
#include <sstream>
#include <linux/types.h>
#include <linux/socket.h>
#include <bitset>

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
    std::bitset<8> data_0;
    std::bitset<8> data_1;
    std::bitset<8> data_2;
    std::bitset<8> data_3;

    data_3 = input_data >> 8*3;
    data_2 = input_data >> 8*2;
    data_1 = input_data >> 8*1;
    data_0 = input_data >> 8*0;

    fake_frame.data[2] = unsigned(data_0.to_ulong());
    fake_frame.data[3] = unsigned(data_1.to_ulong());
    fake_frame.data[4] = unsigned(data_2.to_ulong());
    fake_frame.data[5] = unsigned(data_3.to_ulong());
    


    std::cout<<"Data: \t";
    std::cout<<input_data<<std::endl;
    //std::cout<<unsigned(data_0.to_ulong())<<std::endl;
    //std::cout<<unsigned(data_1.to_ulong())<<std::endl;
    //std::cout<<unsigned(data_2.to_ulong())<<std::endl;
    //std::cout<<unsigned(data_3.to_ulong())<<std::endl;

    std::cout<<"Data Inserted"<<std::endl;
    std::cout<<"The first byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[2])<<std::endl;
    std::cout<<"The second byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[3])<<std::endl;
    std::cout<<"The third byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[4])<<std::endl;
    std::cout<<"The fourth byte: ";
    std::cout<<std::hex<<unsigned(fake_frame.data[5])<<std::endl;
}