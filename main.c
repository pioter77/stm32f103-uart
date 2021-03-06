#include "systick_lib.h"
#include "gp_drive.h"
#include "stm32f10x.h"
#include "uart_drive.h"
#include "str_lib.h"
/*
UART manager:
0-count		incrementing each itme we receive msg
1-signal	variable to detreermine wheather msg is ready
2-bridge	vairable to confirm bridge condition or not
3-Terminator should 1:Termianator /0:Interrupt		flag to decide wheather to choose terminaton character or interrupt timer termination for msg
4-terminator char		specified char vales as terminator charactewr
5-time const 		value time to wait after interr
6-time counter 		this value will be decremeted

this should really be done using the  structure but he wants to keep it simple C so no structs here, only arays
so this mgr arrays should beported in the future to using struct variables or bitfields even in struct
*/
/*
static char USART_1_msg[250];
static unsigned short USART_1_cnt=0;
static unsigned short USART_1_sig=0;
static unsigned short USART_1_bdg=0;

*/
unsigned short uart_1_mgr[7]={0,0,0,0,0,0,0};
static char USART_2_msg[250];
//static unsigned short USART_2_cnt=0;
//static unsigned short USART_2_sig=0;
//static unsigned short USART_2_bdg=0;
unsigned short uart_2_mgr[7]={0,0,0,1,'\n',0,0};

static char USART_3_msg[250];
//static unsigned short USART_3_cnt=0;
//static unsigned short USART_3_sig=0;
//static unsigned short USART_3_bdg=0;
unsigned short uart_3_mgr[7]={0,0,0,1,'\n',0,0};

//static static char chat;
//static static char msg[30]="welcome to the weew!\n";
//static static char msg1[30]="welcome to the noob!\n";
static volatile int sgnl=0;
static volatile _Bool val1=0;
static volatile _Bool tst1val=0;
static volatile int val3=0;
char str1_tst[12];

int main(void)
{
	systick_init();
	UART_init(2,9600);
	UART_init(3,9600);
	delay_MS(100);		//time delay in order to seet the registers
	
UART_send(2,"this is uart 2");//nucle com6
UART_send(3,"this is uart 3");//adapter com10
	int2str(2597,str1_tst);
	val3=char2int("2597");
	while(1)
	{
		//receive char:
		//chat=UART_rx(3);
		//transmiit:
		//UART_tx(3,chat);
	//	delay_MS(100);
		if(uart_2_mgr[1]==1)
		{
		//	UART_send(3,USART_2_msg);
			tst1val=str_findL("Weew","Weewk");
			sgnl=str_len(USART_2_msg);
			val1=str_find("hehe",USART_2_msg);
			uart_2_mgr[1]=0;
			str_empty(USART_2_msg);		//CLEAR_ the string for sending no errors when shorter msg than previous
		}
		if(uart_3_mgr[1]==1)
		{
		//	UART_send(2,USART_3_msg);
			uart_3_mgr[1]=0;
			str_empty(USART_3_msg);		//CLEAR_BIT the string for sending
		
		}
		
	}
}

void USART2_IRQHandler()
{
	UART_isr(2,uart_2_mgr,USART_2_msg);
}
void USART3_IRQHandler()
{
	UART_isr(3,uart_3_mgr,USART_3_msg);
}

void SysTick_Handler(void)
{
	//to nie jest najlepsze rozwiazanie bo trzeba tracic miejsce na strukture do usarta1 mimo ze go sie nie uzywa i on sprawdza potem i probuje go odczytywac?
	//odczytu nie ma chyba bo flaga [0] zawsze na 0
	systick_inter(uart_1_mgr,uart_2_mgr,uart_3_mgr);
}


