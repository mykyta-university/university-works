#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"

void Start_I2C_Transmitting();
void Start_I2C_Receiving();
void Send_I2C_Data(uint8_t data);
uint8_t Read_I2C_Data(I2C_TypeDef* I2Cx);

int main () {

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //Config the I2C
    //Set the clock speed of I2C. It has to be equal with the external device
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    //I2C mode
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    //I2C device adress
    I2C_InitStructure.I2C_OwnAddress1 = 0x33;
    //I2C Acknowladge configuration
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    //Enable the I2C with the prepared configuration
    I2C_Init(I2C1, &I2C_InitStructure);

    //And start the I2C
    I2C_Cmd(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);


    //To send data
    uint8_t _data = 0x01;
    Start_I2C_Transmitting();
    Send_I2C_Data(_data);
    I2C_GenerateSTOP(I2C1, ENABLE);

    //To Receive data
    uint8_t received_i2c_data[2];
    Start_I2C_Receiving();
    received_i2c_data[0] = Read_I2C_Data(I2C1);
    I2C_GenerateSTOP(I2C1, ENABLE);
}


void Start_I2C_Transmitting(){

//For transmiting to the slave, start the data transmitting
    I2C_GenerateSTART(I2C1, ENABLE);
    //Waiting for flag
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    //Send address to slave
    I2C_Send7bitAddress(I2C1, 0x44, I2C_Direction_Transmitter);
//And check the transmitting
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

}

void Start_I2C_Receiving(){

//For transmiting to the slave, start the data transmitting
    I2C_GenerateSTART(I2C1, ENABLE);
    //Waiting for flag
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    //Send address to slave
    I2C_Send7bitAddress(I2C1, 0x44, I2C_Direction_Transmitter);
//And check the transmitting
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

}

void Send_I2C_Data(uint8_t data)
{
    I2C_SendData(I2C1, data);
    // wait for the data trasnmitted flag
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t Read_I2C_Data(I2C_TypeDef* I2Cx){
    uint8_t data = I2C_ReceiveData(I2Cx);
    return data;
}