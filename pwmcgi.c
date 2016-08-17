    #include <stdio.h> //标准输入输出定义    
      
    #include <termios.h> //POSIX 终端控制定义  
      
    #include <unistd.h> //Unix 标准函数定义  
      
    #include <stdlib.h> //标准函数库定义  
      
    #define PWM_IOCTL_SET_FREQ 1  
      
    #define PWM_IOCTL_STOP 0  
      
    #define ESC_KEY 0x1b //定义ESC_KEY 为ESC 按键的键值  
      
    static int getch(void) //定义函数在终端上获得输入，并把输入的量（int）返回  
      
    {  
      
    struct termios oldt,newt; //终端结构体struct termios  
      
    int ch;  
      
    if (!isatty(STDIN_FILENO)) { //判断串口是否与标准输入相连  
      
    fprintf(stderr, "this problem should be run at a terminal\n");  
      
    exit(1);  
      
    }  
      
    // save terminal setting  
      
    if(tcgetattr(STDIN_FILENO, &oldt) < 0) { //获取终端的设置参数  
      
    perror("save the terminal setting");  
      
    exit(1);  
      
    }  
      
    // set terminal as need  
      
    newt = oldt;  
      
    newt.c_lflag &= ~( ICANON | ECHO ); //控制终端编辑功能参数ICANON 表示使用标准输入模式；参数ECH0 表示显示输入字符  
      
    if(tcsetattr(STDIN_FILENO,TCSANOW, &newt) < 0) { //保存新的终端参数  
      
    perror("set terminal");  
      
    exit(1);  
      
    }  
      
    ch = getchar();  
      
    // restore termial setting  
      
    if(tcsetattr(STDIN_FILENO,TCSANOW,&oldt) < 0) { //恢复保存旧的终端参数  
      
    perror("restore the termial setting");  
      
    exit(1);  
      
    }  
      
    return ch;  
      
    }  
      
    static int fd = -1;  
      
    static void close_buzzer(void);  
      
    static void open_buzzer(void) //打开蜂鸣器  
      
    {  
      
    fd = open("/dev/pwm", 0); //打开pwm 设备驱动文件  
      
    if (fd < 0) {  
      
    perror("open pwm_buzzer device"); //打开错误，则终止进程。退出参数为1  
      
    exit(1);  
      
    }  
      
    // any function exit call will stop the buzzer  
      
    atexit(close_buzzer); //退出回调close_buzzer  
      
    }  
      
    static void close_buzzer(void) //关闭蜂鸣器  
      
    {  
      
    if (fd >= 0) {  
      
    ioctl(fd, PWM_IOCTL_STOP); //停止蜂鸣器  
      
    close(fd); //关闭设备驱动文件  
      
    fd = -1;  
      
    }  
      
    }  
      
    static void set_buzzer_freq(int freq)  
      
    {  
      
    // this IOCTL command is the key to set frequency  
      
    int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq); //设置频率  
      
    if(ret < 0) { //如果输入的频率错误  
      
    perror("set the frequency of the buzzer");  
      
    exit(1); //退出，返回1  
      
    }  
      
    }  
      
    static void stop_buzzer(void)  
      
    {  
      
    int ret = ioctl(fd, PWM_IOCTL_STOP); //关闭蜂鸣器  
      
    if(ret < 0) { //如果无法关闭蜂鸣器  
      
    perror("stop the buzzer");  
      
    exit(1); //退出返回1  
      
    }  
   }   



    static void html(void)
    {
     
printf("Content-type: text/html\n\n;charset=gb2312\n\n");
printf("<html>\n");
printf("<head><title>CGI PWM DEMO</title></head>\n");
printf("<body>\n");
printf("<center>\n");
printf("<hr size=5 color=blue width=20%/>\n");
printf("<h1>success</h1>\n");
printf("<hr size=5 color=blue width=20%/>\n");
printf("<center>\n");
printf("</body>\n");

 
    }  
      
    int main(void)  
      
{  
      
    int freq;  
    int fstq=-100;

    

    int key;
    int k=1;
    int i;
     char *data; 
    open_buzzer();//打开蜂鸣器  
printf("Content-type: text/html\n\n;charset=gb2312\n\n");
while(1)

	{

		data=getenv("QUERY_STRING");
		if(sscanf(data,"freq=%ld",&key)!=1)
		{
		k=0;
		printf("ERRO");
                stop_buzzer();  
		exit(1); 
		} 


	     

		 while( k )  
			  {    
				                      

				                       int timer = 50000 ;
				                        
							freq=key;
							 
							while(timer)
									{
									    set_buzzer_freq(freq);
									    timer -= 2;
									}         
							      
								  
					                 set_buzzer_freq(fstq);
				                         html();
                                                   
							 break;  
								      
								  

								      
								 
			      
			 			                    
		      
			   }  

         stop_buzzer();  
						      
	exit(1); 

          }

return 0;


}
