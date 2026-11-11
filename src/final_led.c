#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

int main()
{
		float temperature;
		float total=0;
		float average;
		float mintemp;
		printf("Enter the minimum temperature: ");
		scanf("%f",&mintemp); 
		float maxtemp;
		printf("Enter the maximum temperature: ");
		scanf("%f",&maxtemp); 
		
		
		
		int n,i;
		FILE *Input;
		gpioInitialise();
		gpioSetMode(PIN,PI_OUTPUT);
		gpioWrite(PIN,1);
		gpioWrite(PIN,0);
		
		Input=fopen("temperature.txt","w");
		if(Input==NULL)
		{
			printf("File does not open\n");
			printf("Program exits\n");
			exit(0);
		}
		printf("Please enter no of temperature readings ");
		scanf("%d",&n);
		for (i=1; i<=n;i++)
		{
				printf("Enter temperature readings %d in fahrenhiet: ",i);
				scanf("%f",&temperature);
				total=total+temperature;
				if (temperature>=mintemp&&temperature<=maxtemp)
				{
						printf("Status: Normal\n");
						fprintf(Input,"%.2f - Normal \n", temperature);
						gpioWrite(PIN,0);
				} 
				else
				{
						printf("Status: Warning\n");
						fprintf(Input,"%.2f - Warning \n", temperature);
						gpioWrite(PIN,1);
				}
		}
		average=total/n;
		printf("\n Average Temperature:%.2f F\n",average);
		fprintf(Input,"\n Average Temperature:%.2f F\n",average);
		fclose(Input);
		gpioTerminate();
		return 0;
}
