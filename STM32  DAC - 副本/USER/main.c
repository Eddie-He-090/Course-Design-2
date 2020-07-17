#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "key.h"
#include "dac.h"

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{
    u16 adcx;
    float temp, temp1, temp2;
    u8 t=0;
    u16 dacval=0;
    u8 key;
    u16 G = 0;
	
	short G1 = 0, G2=0, G3=0, G4=0;
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
    delay_init();	    	 //延时函数初始化
    uart_init(9600);	 	//串口初始化为9600
    LED_Init();		  		//初始化与LED连接的硬件接口
    LCD_Init();			   	//初始化LCD
    KEY_Init();				//按键初始化
    Adc_Init();		  		//ADC初始化
    Dac1_Init();		 	//DAC通道1初始化
	
    POINT_COLOR=BLACK;//设置字体为�
    LCD_ShowString(60,50,200,16,16,"20172333090");
    LCD_ShowString(60,70,200,16,16,"DAC");
    //LCD_ShowString(60,90,200,16,16,"2019/12/16");
    LCD_ShowString(60,110,200,16,16,"KEY1:+  KEY0:-");
    LCD_ShowString(60,130,200,16,16,"LEVEL:");
    //显示提示信息
    POINT_COLOR=BLACK;//设置字体为�
    LCD_ShowString(60,150,200,16,16,"DAC VAL:");
    LCD_ShowString(60,170,200,16,16,"DAC VOL:0.000V");
    //LCD_ShowString(60,190,200,16,16,"ADC VOL:0.000V");
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);//????0
		
		LCD_ShowString(60,210,200,16,16,"ONE+:        dB");
		LCD_ShowString(60,230,200,16,16,"ONE-:        dB");
		LCD_ShowString(60,250,200,16,16,"THREE+:      dB");
		LCD_ShowString(60,270,200,16,16,"THREE-:      dB");


    while(1)
    {
        t++;
        key=KEY_Scan(0);
        if(key==KEY1_PRES)
        {
            G++;
            //if (G>53) G = 0;
            if(dacval<4000) dacval+=31;
            DAC_SetChannel1Data(DAC_Align_12b_R, dacval);
            //if(dacval<4000)dacval+=200;
            //DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//??DAC?
        } else if(key==KEY0_PRES)
        {
            if (G>0) G--;
            else G=0;
            if(dacval>31) dacval-=31;
            else dacval=0;
            DAC_SetChannel1Data(DAC_Align_12b_R, dacval);
            //if(dacval>200)dacval-=200;
            //else dacval=0;
            //DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//??DAC?
        }

        if(t==10||key==KEY1_PRES||key==KEY0_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
        {
            LCD_ShowxNum(124,130,G,4,16,0);
            adcx=DAC_GetDataOutputValue(DAC_Channel_1);//??????DAC??
            LCD_ShowxNum(124,150,adcx,4,16,0);     	//显示DAC寄存器值
            temp=(float)adcx*(3.3/4096);			//得到DAC电压值
            adcx=temp;
					temp1=temp;
            LCD_ShowxNum(124,170,temp1,1,16,0);     	//显示电压值整数部分
            temp-=adcx;
            temp*=1000;
					temp2=temp+1;
            LCD_ShowxNum(140,170,temp2,3,16,0X80); 	//显示电压值的小数部分
            adcx=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值
            temp=(float)adcx*(3.3/4096);			//得到ADC电压值
            adcx=temp;
            //LCD_ShowxNum(124,190,temp,1,16,0);     	//显示电压值整数部分
            temp-=adcx;
            temp*=1000;
            //LCD_ShowxNum(140,190,temp,3,16,0X80); 	//显示电压值的小数部分
            LED0=!LED0;
            t=0;
					
					G1=G+20;
					if (G1>=31){
					G1=31;
						LCD_ShowString(200,210,200,16,16,"X");
					}
					if (G1<=30){
						LCD_ShowString(200,210,200,16,16," ");
					}
					LCD_ShowxNum(124,210,G1,4,16,0);
					
					G2=20-G;
					if (G2<=10){
					G2=10;
						LCD_ShowString(200,230,200,16,16,"X");
					}
					if (G2>=11){
					  LCD_ShowString(200,230,200,16,16," ");
					}
					LCD_ShowxNum(124,230,G2,4,16,0);
					
					G3=G+40;
					if (G3>=51){
					G3=51;
						LCD_ShowString(200,250,200,16,16,"X");
					}
					if (G3<=50){
						LCD_ShowString(200,250,200,16,16," ");
					}
					LCD_ShowxNum(124,250,G3,4,16,0);
					
					G4=40-G;
					if (G4<=19){
					G4=19;
						LCD_ShowString(200,270,200,16,16,"X");
					}
					if (G4>=20){
						LCD_ShowString(200,270,200,16,16," ");
					}
					LCD_ShowxNum(124,270,G4,4,16,0);
        }

//        if(t==10||key==KEY0_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
//        {
//            LCD_ShowxNum(124,130,G,4,16,0);
//            adcx=DAC_GetDataOutputValue(DAC_Channel_1);//??????DAC??
//            LCD_ShowxNum(124,150,adcx,4,16,0);     	//显示DAC寄存器值
//            temp=(float)adcx*(3.3/4096);			//得到DAC电压值
//            adcx=temp;
//            LCD_ShowxNum(124,170,temp,1,16,0);     	//显示电压值整数部分
//            temp-=adcx;
//            temp*=1000;
//            LCD_ShowxNum(140,170,temp,3,16,0X80); 	//显示电压值的小数部分
//            adcx=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值
//            temp=(float)adcx*(3.3/4096);			//得到ADC电压值
//            adcx=temp;
//            LCD_ShowxNum(124,190,temp,1,16,0);     	//显示电压值整数部分
//            temp-=adcx;
//            temp*=1000;
//            LCD_ShowxNum(140,190,temp,3,16,0X80); 	//显示电压值的小数部分
//            LED0=!LED0;
//            t=0;
//        }

        delay_ms(10);
    }
}

