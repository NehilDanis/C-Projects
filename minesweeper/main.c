#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
int main ()
{
    int array [10][10]={0};
    int i,j;
    int a;
    int number;
    int mine;
    srand(time(NULL));//I used the srand(time(NULL)) to assign the values into the different places when the time changed.
    printf("how many mines do you want in the minefield?: ");
    scanf("%d",&mine);
    printf("   ");
    for(number=0;number<mine;number++)//I did this loop to determine places of the mines.
    {
        i=rand()%10;
        j=rand()%10;
        if(array[i][j]==9)//This loop determine places of the mines randomly.So if I use this 'if condition' ,mines won't be the same place.
        {
        	number=number-1;
        }
        else
        {
        	array[i][j]=9;//When I determined the place of mine,'else condition' put 9 into the place of array[i][j]       
		 }
     
    }
    for(i=0;i<10;i++)
	{
		 for(j=0;j<10;j++)
            {
				if(array[i][j]==9)//this 'if condition' check to we can find the mine or not.
				{


						if((i-1)>=0 && j-1>=0 && array[i-1][j-1]!=9)//This if statement increase the upper corner of the left side of mine.
						{                                            
							array[i-1][j-1]++;						
						}
						if(i+1<=9 && j+1<=9 && array[i+1][j+1]!=9)//This if statement increase the down corner of the right side of mine.
						{
							array[i+1][j+1]++;
						}
						if(i+1<=9 && j-1>=0 && array[i+1][j-1]!=9)//This if statement increase the down corner of the left side of mine.
						{
							array[i+1][j-1]++;
						}
						if(i-1>=0 && j+1<=9 && array [i-1][j+1]!=9)//This if statement increase the upper corner of the right side of mine.
						{
							array[i-1][j+1]++;
						}
						if(j-1>=0 && array[i][j-1]!=9)//This if statement increase the left side of mine.
						{
							array[i][j-1]++;
						}
						if(j+1<=9 && array[i][j+1]!=9)//This if statement increase the right side of mine.
						{
							array[i][j+1]++;
						}
						if(i-1>=0 && array[i-1][j]!=9)//This if statement increase the upper side of mine.
						{
							array[i-1][j]++;
						}
						if(i+1<=9 && array[i+1][j]!=9)//This if statement increase the down side of mine.
						{
							array[i+1][j]++;
						}	
				}
			}
	}
	for(a=1;a<11;a++)//I did this loop to print the upper values of the chart.
    {
        printf(" %d",a);
    }
    printf("\n");
    printf("   ");
    for(a=1;a<12;a++)//I did this loop to print the lines of under the upper values of the chart.
    {
        printf("--");
    }
    printf("\n");
    for(i=0;i<10;i++)//I did this loop to print the left side of chart.
        {
            if(i<9)//I did this if -else statement to blocked to float the number.because,for example If the value of i equal to 9,this statement will print 10.
            {	  //So the column will float.I used this if-else statement to blocked this wrong statement.
                printf("%d |",(i+1));
            }
            else if(i==9)
            {
                printf("%d|",(i+1));
            }
            for(j=0;j<10;j++)//I did this loop to print array or M for mines places.
            {
    
				if (array[i][j]==9)//If this loop  experince to 9,this will print M for every mines.
				{
					printf(" M");
				}
				else//For the other places else statement print array.
				{
				printf(" %d",array[i][j]);
				}
			}
			printf("\n");
		}
		
		
		return 0;
}

				
