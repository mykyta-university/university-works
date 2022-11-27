/*
 * Some code was taken from https://drive.google.com/file/d/1TWEiZ-7LOKVC5IeI7e-g4-rp27I0S0gf/view
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

static uint8_t command = 0;

void init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    USART_InitTypeDef USART_InitStruct;
    //USART_InitStruct.USART_BaudRate = ;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl =
            USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStruct);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void){
    if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
        USART_ClearITPendingBit(USART1,
                                USART_IT_RXNE); static uint8_t cnt = 0;
        uint8_t t = USART_ReceiveData(USART1);
        command = t;
    }
}

void delay(int count) {
    while(--count);
}

int main(void) {
    init();
    uint8_t command = 0;
    while (1) {
        delay(1000);
        USART_SendData(USART1, command);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        command++;
        if (0xff == command) command = 0;
    }
}

