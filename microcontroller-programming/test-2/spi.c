/*
 * Some code was taken from https://drive.google.com/file/d/1TWEiZ-7LOKVC5IeI7e-g4-rp27I0S0gf/view
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "misc.h"

#define SPI_PINS GPIO_Pin_5 | \
GPIO_Pin_6 | \
GPIO_Pin_7

void init(void);
void delay(int count);

void SPI1_IRQHandler(void) {
    int res;
    if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET)
    { SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
        res = SPI_I2S_ReceiveData(SPI1);
    }
}

int main(void)
{
    init();
    int sendData = 0;
    while(1)
    {
        delay(100);
        SPI_I2S_SendData(SPI2, sendData);
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
        sendData++;
        if (sendData == 0xff) sendData = 0;
    }
}

void init(void) {
    GPIO_InitTypeDef gpio_init;
    SPI_InitTypeDef spi_init;
    NVIC_InitTypeDef nvic_init;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |
                           RCC_AHB1Periph_GPIOB |
                           RCC_AHB1Periph_GPIOC, ENABLE);

/* Configure slave pins */
    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_Pin = SPI_PINS;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOA, &gpio_init);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);
    gpio_init.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    SPI_I2S_DeInit(SPI1);
    spi_init.SPI_Mode = SPI_Mode_Slave;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_DataSize = SPI_DataSize_8b;
    spi_init.SPI_CPOL = SPI_CPOL_Low; spi_init.SPI_CPOL =
                                              SPI_CPHA_1Edge;
    spi_init.SPI_FirstBit = SPI_FirstBit_MSB;

    spi_init.SPI_NSS = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_Init(SPI1, &spi_init);
    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    SPI_StructInit(&spi_init);
    SPI_I2S_DeInit(SPI2);
    spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_DataSize = SPI_DataSize_8b;
    spi_init.SPI_CPOL = SPI_CPOL_Low; spi_init.SPI_CPOL =
                                              SPI_CPHA_1Edge;
    spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
    spi_init.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI2, &spi_init);
    nvic_init.NVIC_IRQChannel = SPI1_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&nvic_init);
    SPI_Cmd(SPI1, ENABLE);
    SPI_Cmd(SPI2, ENABLE);
}
void delay(int count) {
    while(--count);
}