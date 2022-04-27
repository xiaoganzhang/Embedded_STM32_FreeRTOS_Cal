
void Draw_Keyboard_Layout(void)
{
  	LCD_DrawRectangle(5,110,234,314);//矩形框
	
	LCD_DrawLine(62,110,62,314);//三条竖线
	LCD_DrawLine(119,110,119,314);
	LCD_DrawLine(177,110,177,314);
	
	LCD_DrawLine(5,161,234,161);//三条横线
	LCD_DrawLine(5,212,234,212);
	LCD_DrawLine(5,263,234,263);
	
	LCD_ShowString(31,131,200,16,16,"1");//写数字和符号
	LCD_ShowString(88,131,200,16,16,"2");
	LCD_ShowString(145,131,200,16,16,"3");
	LCD_ShowString(202,131,200,16,16,"+");
	
	LCD_ShowString(31,182,200,16,16,"4");
	LCD_ShowString(88,182,200,16,16,"5");
	LCD_ShowString(145,182,200,16,16,"6");
	LCD_ShowString(202,182,200,16,16,"-");
	
	LCD_ShowString(31,233,200,16,16,"7");
	LCD_ShowString(88,233,200,16,16,"8");
	LCD_ShowString(145,233,200,16,16,"9");
	LCD_ShowString(202,233,200,16,16,"*");
	
	LCD_ShowString(31,280,200,16,16,".");
	LCD_ShowString(88,284,200,16,16,"0");
	LCD_ShowString(145,284,200,16,16,"=");
	LCD_ShowString(202,284,200,16,16,"/");
	
	LCD_DrawLine(5,68,234,68);
	LCD_ShowString(5,50,200,16,16,"process:");
	LCD_ShowString(5,75,200,16,16,"answer:");
	LCD_DrawLine(5,93,234,93);
}
 
//触摸扫描函数 .：10  =：11  +：12  -：13  *：14  /：15 ，没有触摸或者触摸到键盘以外的位置返回16
int Touch_Return(void)
{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{		
			if(tp_dev.x[0]>=5&&tp_dev.x[0]<=62&&tp_dev.y[0]>=110&&tp_dev.y[0]<=161)//按键按下会执行的操作
			{
				vTaskResume(Calculate_Task_Handler);
				return 1;
			}
			
			if(tp_dev.x[0]>=5&&tp_dev.x[0]<=62&&tp_dev.y[0]>=161&&tp_dev.y[0]<=212)
			{
				vTaskResume(Calculate_Task_Handler);
				return 4;
			}
			
			if(tp_dev.x[0]>=5&&tp_dev.x[0]<=62&&tp_dev.y[0]>=212&&tp_dev.y[0]<=263)
			{
				vTaskResume(Calculate_Task_Handler);
				return 7;
			}
			
			if(tp_dev.x[0]>=5&&tp_dev.x[0]<=62&&tp_dev.y[0]>=263&&tp_dev.y[0]<=314)
			{
				vTaskResume(Calculate_Task_Handler);
				return 10;
			}
			
			if(tp_dev.x[0]>=62&&tp_dev.x[0]<=119&&tp_dev.y[0]>=110&&tp_dev.y[0]<=161)//第二列
			{
				vTaskResume(Calculate_Task_Handler);
				return 2;
			}
			
			if(tp_dev.x[0]>=62&&tp_dev.x[0]<=119&&tp_dev.y[0]>=161&&tp_dev.y[0]<=212)
			{
				vTaskResume(Calculate_Task_Handler);
				return 5;
			}
			
			if(tp_dev.x[0]>=62&&tp_dev.x[0]<=119&&tp_dev.y[0]>=212&&tp_dev.y[0]<=263)
			{
				vTaskResume(Calculate_Task_Handler);
				return 8;
			}
			
			if(tp_dev.x[0]>=62&&tp_dev.x[0]<=119&&tp_dev.y[0]>=263&&tp_dev.y[0]<=314)
			{
				vTaskResume(Calculate_Task_Handler);
				return 0;
			}
			
			if(tp_dev.x[0]>=119&&tp_dev.x[0]<=177&&tp_dev.y[0]>=110&&tp_dev.y[0]<=161)//第三列
			{
				vTaskResume(Calculate_Task_Handler);
				return 3;
			}
			
			if(tp_dev.x[0]>=119&&tp_dev.x[0]<=177&&tp_dev.y[0]>=161&&tp_dev.y[0]<=212)
			{
				vTaskResume(Calculate_Task_Handler);
				return 6;
			}
			
			if(tp_dev.x[0]>=119&&tp_dev.x[0]<=177&&tp_dev.y[0]>=212&&tp_dev.y[0]<=263)
			{
				vTaskResume(Calculate_Task_Handler);
				return 9;
			}
			
			if(tp_dev.x[0]>=119&&tp_dev.x[0]<=177&&tp_dev.y[0]>=263&&tp_dev.y[0]<=314)
			{
				vTaskResume(Calculate_Task_Handler);
				return 11;
			}
			
			if(tp_dev.x[0]>=177&&tp_dev.x[0]<=234&&tp_dev.y[0]>=110&&tp_dev.y[0]<=161)//第四列
			{
				vTaskResume(Calculate_Task_Handler);
				return 12;
			}
			if(tp_dev.x[0]>=177&&tp_dev.x[0]<=234&&tp_dev.y[0]>=161&&tp_dev.y[0]<=212)
			{
				vTaskResume(Calculate_Task_Handler);
				return 13;
			}
			
			if(tp_dev.x[0]>=177&&tp_dev.x[0]<=234&&tp_dev.y[0]>=212&&tp_dev.y[0]<=263)
			{
				vTaskResume(Calculate_Task_Handler);
				return 14;
			}
			
			if(tp_dev.x[0]>=177&&tp_dev.x[0]<=234&&tp_dev.y[0]>=263&&tp_dev.y[0]<=314)
			{
				vTaskResume(Calculate_Task_Handler);
				return 15;
			}
			else
			return 16;
		}
		else //没有按键按下的时候
		{
			delay_ms(10);	 
      return 16;	    
	  }
}
 
void calculate_task(void *pvParameters)
{
	int stage=0;//stage：用于判断第一个输入数的小数点前部分和后部分,输入第一个数时按下小数点置1。
	int stage2=0;//stage：用于判断第二个输入数的小数点前部分和后部分,输入第一个数时按下小数点置1。
	int stage1=0;//用于判断输入的是第几个数，按下+-*/时置1。
	int stage3=0;//按下=置1
	int Number_Distance=68;
	int Number2_Distance=60;
	int Number_Before_Point=0;//记录第一个数小数点后多少位，用于算number大小
	int Number1_Before_Point=0;//记录第一个数小数点后多少位，用于算number大小
	int Calculate_Stage;//存储按的是+-*/，+：1  -：2  *：3  /：4
	
	double number=0;//第一个数存储
	double number1=0;//第二个数存储
	double number2=0;//结果存储
 
  int Number2_Int=1;//记录number2整数部分有几位
	int Number2_Int1;//记录number2整数部分有几位时的中间变量
	int Number2_Float;//显示number2小数部分
	
	while(1)
	{
    if(stage1==0&&(Touch_Return_Number==0||Touch_Return_Number==1||Touch_Return_Number==2||Touch_Return_Number==3||Touch_Return_Number==4||Touch_Return_Number==5||
			Touch_Return_Number==6||Touch_Return_Number==7||Touch_Return_Number==8||Touch_Return_Number==9||Touch_Return_Number==10))//第一个数处理
		{
			if(stage==0)//小数点前面部分
			{
			 if(Touch_Return_Number==10)
		   {
				 stage=1;//按小数点stage置1
				 LCD_ShowString(Number_Distance,50,200,16,16,".");
				 Number_Distance+=8;
				 vTaskSuspend(Calculate_Task_Handler);
			  }
			 else
			 {	 
				 LCD_ShowNum(Number_Distance,50,Touch_Return_Number,1,16);
				 Number_Distance+=8;
				 number=number*10+Touch_Return_Number;
				 //printf("%d\r\n",number);
				 vTaskSuspend(Calculate_Task_Handler);
			 }
			}
			else//小数点后面部分
			{
				Number_Before_Point++;
				LCD_ShowNum(Number_Distance,50,Touch_Return_Number,1,16);
				Number_Distance+=8;
				number=number+Touch_Return_Number/(10.0*Number_Before_Point);
				vTaskSuspend(Calculate_Task_Handler);
			 
			}
		}
		
		if(stage3==0&&stage1==0&&(Touch_Return_Number==12||Touch_Return_Number==13||Touch_Return_Number==14||Touch_Return_Number==15))//按下+-*/之后把stage1置1
		{
		 stage1=1;
			
		 if(Touch_Return_Number==12)
		 {	 
		  LCD_ShowString(Number_Distance,50,200,16,16,"+");
			Calculate_Stage=1;
			vTaskSuspend(Calculate_Task_Handler);
		 }
		 if(Touch_Return_Number==13)
		 {	 
		  LCD_ShowString(Number_Distance,50,200,16,16,"-");
		  Calculate_Stage=2;
			vTaskSuspend(Calculate_Task_Handler);
		 }
		 if(Touch_Return_Number==14)
		 {	 
		  LCD_ShowString(Number_Distance,50,200,16,16,"*");
			Calculate_Stage=3;
			vTaskSuspend(Calculate_Task_Handler);
		 }
		 if(Touch_Return_Number==15)
		 {	 
		  LCD_ShowString(Number_Distance,50,200,16,16,"/");
			Calculate_Stage=4;
			vTaskSuspend(Calculate_Task_Handler);
		 }
		 Number_Distance+=8;
		}
		
		if(stage3==0&&stage1==1&&(Touch_Return_Number==0||Touch_Return_Number==1||Touch_Return_Number==2||Touch_Return_Number==3||Touch_Return_Number==4||Touch_Return_Number==5||
			Touch_Return_Number==6||Touch_Return_Number==7||Touch_Return_Number==8||Touch_Return_Number==9||Touch_Return_Number==10))//第二个数处理
		{
			if(stage2==0)//小数点前面部分
			{
			 if(Touch_Return_Number==10)
		   {
				 stage2=1;//按小数点stage置1
				 LCD_ShowString(Number_Distance,50,200,16,16,".");
				 Number_Distance+=8;
				 vTaskSuspend(Calculate_Task_Handler);
			  }
			 else
			 {	 
				 LCD_ShowNum(Number_Distance,50,Touch_Return_Number,1,16);
				 Number_Distance+=8;
				 number1=number1*10+Touch_Return_Number;
				 //printf("%d\r\n",number);
				 vTaskSuspend(Calculate_Task_Handler);
			 }
			}
			else//小数点后面部分
			{
				Number1_Before_Point++;
				LCD_ShowNum(Number_Distance,50,Touch_Return_Number,1,16);
				Number_Distance+=8;
				number1=number1+Touch_Return_Number/(10.0*Number1_Before_Point);
				vTaskSuspend(Calculate_Task_Handler);
			}
		}
		
		if(Touch_Return_Number==11&&stage1==1&&stage3==0)//按下=
		{
			stage3=1;
			if(Calculate_Stage==1)
			number2=number+number1;
			
			if(Calculate_Stage==2)
			number2=number-number1;
			
			if(Calculate_Stage==3)
			number2=number*number1;
			
			if(Calculate_Stage==4)
			{
			 if(number1==0)
			 {
				 LCD_ShowString(Number2_Distance,75,200,16,16,"error");
				 vTaskSuspend(Calculate_Task_Handler);
			 }
			 else
			 number2=number/number1;
			 }
			 
			
			Number2_Int1=(int)number2;
			
			while(1)
			{
			  if((Number2_Int1/10)==0)
				break;
				else
				{
				 Number2_Int++;
				 Number2_Int1/=10;
				}
			}	
			printf("%d\r\n",Number2_Int);
			printf("%d\r\n",(int)number2);
			printf("%f\r\n",number);
			printf("%f\r\n",number1);
			printf("%f\r\n",number2);
			if(number2<0)
			{
				LCD_ShowString(Number2_Distance,75,200,16,16,"-");	
			  Number2_Distance+=8;
				number2=-number2;
			}
			LCD_ShowNum(Number2_Distance,75,(int)number2,Number2_Int,16);
			Number2_Distance=Number2_Distance+8*Number2_Int;
		  LCD_ShowString(Number2_Distance,75,200,16,16,".");
			Number2_Distance+=8;
			if((((int)(number2*10))%10)==0)
			{
			 LCD_ShowNum(Number2_Distance,75,0,1,16);
			 Number2_Distance+=8;
			}
			Number2_Float=(int)((number2-(int)number2)*1000);
			LCD_ShowNum(Number2_Distance,75,Number2_Float,3,16);
			vTaskSuspend(Calculate_Task_Handler);
		
		}
	
	}
}  
