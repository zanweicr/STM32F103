#include "stm32f10x.h"



void My_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);					//A��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);					//����1ʹ��
	
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;					//���츴�����
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;								//GPIOA_9 USART_TX
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;					
	GPIO_Init(GPIOA,&GPIO_InitStrue);										//��ʼ��
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;		//��������
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;							//GPIOA_9 USART_RX
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;					
	GPIO_Init(GPIOA,&GPIO_InitStrue);										//��ʼ��

	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStrue);
	
	
	USART_Cmd(USART1,ENABLE);


	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);


	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;							//ʹ���ж�
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; 	//��ռ���ȼ�����Ϊ1
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;					//��Ӧ���ȼ�����Ϊ1
	NVIC_Init(&NVIC_InitStrue);


}

void USART1_IRQHandler(void)
{
	u8 res;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res=USART_ReceiveData(USART1);
		
		USART_SendData(USART1,res);
	}
	

}


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART_Init();
	while(1);
 
}
