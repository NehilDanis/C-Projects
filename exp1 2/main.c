#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printToTheFile(int**,int,double,double);//This prints the results on the output file.
int control(int**,int,int,int);//This controls all variables.
void assignRandomly(int**,int,double*);//I assign random variables to my matrix by this function. 
double mean(double*,int);//This is for calculating the mean.
double standartdev(double*,double,int);//This is for calculating the standart deviation.
double sqroot(double);
int controlRightSideForWater(int**,int,int,int);
int controlRightSideForAir(int**,int,int,int);
int controlLeftSideForWater(int**,int,int,int);
int controlLeftSideForAir(int**,int,int,int);
int controlTopSideForWater(int**,int,int,int);
int controlTopSideForAir(int**,int,int,int);
int controlBottomSideForWater(int**,int,int,int);
int controlBottomSideForAir(int**,int,int,int);


int main(int argc,char *argv[]){//My program wants the user to give variables.Because of that I used argc and argv.
	srand(time(NULL));//This is for changing results that depend on computer's time.
	int matrix=atoi(argv[1]);//argv is a char array.So I used atoi to turn the char value into the integer value.(matrix*matrix=N*N)
	int iteration=atoi(argv[2]);//This keeps the number that gives us how many times the program will be executed.
	int counter=0;//This counts the number of iteration.
	double meanValue=0.0;
	double standartDev=0.0;
	double* possibilityArray=(double*)calloc(iteration,sizeof(double));//This array will keep the possibility result of every iteration.
	while(counter<iteration){
		int i;
		double a=0;
		double* numberOfOpenBoxes;//Start of every iteration the value of this variable will be changed by zero.
		numberOfOpenBoxes=&a;
		int** matrixShape=(int**)calloc(matrix,sizeof(int*));//This is for my matrix.
		for(i=0;i<matrix;i++){
			matrixShape[i]=(int*)calloc(matrix,sizeof(int));	
		}
		assignRandomly(matrixShape,matrix,numberOfOpenBoxes);//Function call of assignRandomly.
		possibilityArray[counter]=*(numberOfOpenBoxes)/(double)(matrix*matrix);
		
		if(counter==iteration-1){//We just want to print the last iteration of matrix.
			meanValue=mean(possibilityArray,iteration);
			standartDev=standartdev(possibilityArray,meanValue,iteration);
			printToTheFile(matrixShape,matrix,meanValue,standartDev);//Function call of printToTheFile.
			free(possibilityArray);
			for(i=0;i<matrix;i++){
				free(matrixShape[i]);
			}
			free(matrixShape);
			
		}
		counter++;//This helps to provide the base case of this while loop.
	}
	return 0;

}

void assignRandomly(int** matrixShape,int matrix,double *numberOfOpenBoxes){//Here we assign random values to the matrix.
	int value=1;
	int x,y;//These are for my random coordinates.
	while(value==1){
		x=rand()%matrix;
		y=rand()%matrix;
		if(matrixShape[x][y]==0){//I only assign the random values to the boxes that are represented by 0.
			if(x==0){//If the random coordinate stays any place in my zeroth row,The program will assign 2 this box.
				matrixShape[x][y]=2;
				value=control(matrixShape,matrix,x,y);//I called control function.If it returns 1,this iteration is gonna be end.
				*numberOfOpenBoxes=*numberOfOpenBoxes+1.0;//Because of opening a box,I have to increase the numberOfBoxes value.
				
			}
			else{//If my random coordinate stays in somewhere that place is different from a place in zeroth row,the program will assign 1.
				matrixShape[x][y]=1;
				value=control(matrixShape,matrix,x,y);//I called control function.If it returns 1,this iteration is gonna be end.
				*numberOfOpenBoxes=*numberOfOpenBoxes+1.0;//Because of opening a box,I have to increase the numberOfBoxes value.
			}
		}	
	}
}


int control(int** matrixShape,int matrix,int x,int y){//This controls the sides of randomly opened boxes.
	int controlValue1=1,controlValue2=1,controlValue3=1,controlValue4=1;//This ones handle to control the return values.
	if(matrixShape[x][y]==1){
		if(x>0 && x<matrix-1){
			if(y==0){
				controlValue1=controlRightSideForAir(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForAir(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForAir(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y==matrix-1){
				controlValue4=controlLeftSideForAir(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForAir(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForAir(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y>0 && y<matrix-1){
				controlValue1=controlRightSideForAir(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForAir(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForAir(matrixShape,matrix,x,y);
				controlValue4=controlLeftSideForAir(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
		}
		else if(x==matrix-1){
			controlValue2=controlTopSideForAir(matrixShape,matrix,x,y);
			if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
			}
		}
		
	}
	else if(matrixShape[x][y]==2){
		if(x==0){
			controlValue3=controlBottomSideForWater(matrixShape,matrix,x,y);
			if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
			}
		}
		else if(x==matrix-1){
			if(y==0){
				controlValue1=controlRightSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y==matrix-1){
				controlValue4=controlLeftSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y>0 && y<matrix-1){
				controlValue1=controlRightSideForWater(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForWater(matrixShape,matrix,x,y);
				controlValue4=controlLeftSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
				
			}
		}
		else if(x>0 && x<matrix-1){
			if(y==0){
				controlValue1=controlRightSideForWater(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForWater(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y==matrix-1){
				controlValue2=controlTopSideForWater(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForWater(matrixShape,matrix,x,y);
				controlValue4=controlLeftSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
			}
			else if(y>0 && y<matrix-1){
				controlValue1=controlRightSideForWater(matrixShape,matrix,x,y);
				controlValue2=controlTopSideForWater(matrixShape,matrix,x,y);
				controlValue3=controlBottomSideForWater(matrixShape,matrix,x,y);
				controlValue4=controlLeftSideForWater(matrixShape,matrix,x,y);
				if(controlValue1==0 || controlValue2==0 || controlValue3==0 || controlValue4==0){
					return 0;
				}
				
			}
			
		}
		
	}
	
	if(x==matrix-1){
		if(matrixShape[x][y]==2){
			return 0;
		}
	}
	
	return 1;
	
}


int controlRightSideForWater(int** matrixShape,int matrix,int x,int y){//This is going to control the right side of box that filled with water.
	int value=1;
	if(matrixShape[x][y+1]==1){
		matrixShape[x][y+1]=2;
		value=control(matrixShape,matrix,x,y+1);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlRightSideForAir(int** matrixShape,int matrix,int x,int y){//This is going to control the right side of box that filled with air.
	int value=1;
	if(matrixShape[x][y+1]==2){
		matrixShape[x][y]=2;
		value=control(matrixShape,matrix,x,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlLeftSideForWater(int** matrixShape,int matrix,int x,int y){//This is going to control the left side of box that filled with water.
	int value=1;
	if(matrixShape[x][y-1]==1){
		matrixShape[x][y-1]=2;
		value=control(matrixShape,matrix,x,y-1);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlLeftSideForAir(int** matrixShape,int matrix,int x,int y){//This is going to control the left side of box that filled with air.
	int value=1;
	if(matrixShape[x][y-1]==2){
		matrixShape[x][y]=2;
		value=control(matrixShape,matrix,x,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlTopSideForWater(int** matrixShape,int matrix,int x,int y){//This is going to control the top side of box that filled with water.
	int value=1;
	if(matrixShape[x-1][y]==1){
		matrixShape[x-1][y]=2;
		value=control(matrixShape,matrix,x-1,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlTopSideForAir(int** matrixShape,int matrix,int x,int y){//This is going to control the top side of box that filled with air.
	int value=1;
	if(matrixShape[x-1][y]==2){
		matrixShape[x][y]=2;
		value=control(matrixShape,matrix,x,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlBottomSideForWater(int** matrixShape,int matrix,int x,int y){//This is going to control the bottom side of box that filled with water.
	int value=1;
	if(matrixShape[x+1][y]==1){
		matrixShape[x+1][y]=2;
		value=control(matrixShape,matrix,x+1,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}
int controlBottomSideForAir(int** matrixShape,int matrix,int x,int y){//This is going to control the bottom side of box that filled with air.
	int value=1;
	if(matrixShape[x+1][y]==2){
		matrixShape[x][y]=2;
		value=control(matrixShape,matrix,x,y);
		if(value==0){
			return 0;
		}
	}
	return 1;
}

double mean(double* possibilityArray,int iteration){//This is going to calculate the mean value.
	double sum=0;
	double ite=iteration;
	int i;
	for(i=0;i<iteration;i++){
		sum+=possibilityArray[i];
	}
	return (sum/ite);
	
}

double standartdev(double* possibilityArray,double meanValue,int iteration){//This is going to calculate the standart deviation value.
	double sum=0;
	double ite=iteration;
	int i;
	for(i=0;i<iteration;i++){
		sum+=(possibilityArray[i]-meanValue)*(possibilityArray[i]-meanValue);
	}
	double x=sqroot(sum/(ite-1));
	return x;
}

void printToTheFile(int** matrixShape,int matrix,double mean,double stddev){//This function is used for printing the results.
	int i,j;
	FILE *write;//This is my file pointer to point the output file .
    write = fopen("output.txt","w");//I opened the file to write something in the output file.
    
	for(i=0;i<matrix;i++){//Here I printed the matrix.
		for(j=0;j<matrix;j++){
			fprintf(write," %d ",matrixShape[i][j]);
		}
		fprintf(write,"\n");
	} 
	
	fprintf(write,"\n");
	fprintf(write,"mean()  \t= %f\n",mean);
	fprintf(write,"stddev()\t= %f\n",stddev);
	
	fclose(write);
      
}

double sqroot(double square){//This is for calculating the square root.
    double root=square/3;
    int i;
    if (square <= 0) return 0;
    for (i=0; i<32; i++)
        root = (root + square / root) / 2;
    return root;
}


