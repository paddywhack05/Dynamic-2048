#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    void clearScreen(){
    system("cls");
    }
#else
#include <termios.h>
#include <unistd.h> 
int getch(void){
  struct termios oldattr, newattr;
  unsigned char ch;
  int retcode;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr=oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  retcode=read(STDIN_FILENO, &ch, 1);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return retcode<=0? EOF: (int)ch;
}
void clearScreen(){
    system("clear");
}
#endif

void resetGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    array[i] = calloc(rows,sizeof(int));
}

return;
}
int findNumEmpty(int rows, int cols ,int **array){    
int a,b;
int num=0;
for(a=0; a < cols; a++){
  for(b=0; b<rows;b++){
    if(array[a][b]==0){
        num++;
    }
  }
}
return num;
}
void printGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    printf("| ");
  for (j = 0; j < rows; j++) {
  if(array[i][j]==0){
    printf("    | ",array[i][j]);
  }
  else if(array[i][j]<10){
    printf(" %d  | ",array[i][j]);
  }
  else if(array[i][j]>10&&array[i][j]<100){
    printf(" %d | ",array[i][j]);
  }else if(array[i][j]>100){
    printf("%d | ",array[i][j]);
  }else if(array[i][j]>1000){
    printf("%d| ",array[i][j]);
  }else{
    printf("%d|",array[i][j]);
  }
    if(j==rows-1){
        printf("\n");
    }
  }
}
}
int spawnNum(int rows, int cols ,int **array){
     int emptyPlaces = findNumEmpty(rows, cols ,array);
     if(emptyPlaces==0){
        return 1;
     }
    int rNum = (rand() % (10 - 1 + 1)) + 1;
    int rpNum = (rand() % (emptyPlaces - 1 + 1));
    int num = 0;
     //printf("rNum = %d\nempty places = %d\n",rNum,emptyPlaces);
     int blockNum=0;
     if(rNum == 10){
        blockNum=4;
     }else{
        blockNum=2;
     }

    for(int i=0; i < cols; i++){
     for(int j=0; j<rows;j++){
     if(array[i][j]==0){
        if(num==rpNum){
            array[i][j]=blockNum;
            //printf("NUM %d",num);
            num++;
        }else{
            num++;
        }
     }
     }
     if(num == rpNum){
        //printf("Num reached num=%d rpNum=%d",num,rpNum);
     }
    }
   //  printf("block num = %d\n",blockNum);
     return 0;
}
int CheckRight(int rows,int cols, int**array){
for(int i=0;i < cols; i++){
    for(int j=0;j<rows-1;j++){
        if(array[i][j]!=0&&array[i][j+1]==0){
            return 0;
        }
    }
}
return 1;
}
int CheckLeft(int rows,int cols, int**array){
for(int i=0;i < cols; i++){
    for(int j=rows-1;j>0;j--){
        if(array[i][j]!=0&&array[i][j-1]==0){
            return 0;
        }
    }
}
return 1;
}
int CheckUp(int rows,int cols, int**array){
    for(int j=0;j < rows; j++){
    for(int i=cols-1;i>0;i--){
        if(array[i][j]!=0&&array[i-1][j]==0){
            return 0;
        }
    }
}
return 1;
}
int CheckDown(int rows,int cols, int**array){
 for(int j=0;j < rows; j++){
    for(int i=0;i<cols-1;i++){
        if(array[i][j]!=0&&array[i+1][j]==0){
            return 0;
        }
    }
}
return 1;
}
int CheckHorizontal(int rows,int cols, int**array){
    for(int i=0;i < cols; i++){
    for(int j=rows-1;j>0;j--){
if(array[i][j]!=0&&array[i][j]==array[i][j-1]){
            return 0;
        }
    }
}
return 1;
}
int CheckVertical(int rows,int cols, int**array){
        for(int j=0;j < rows; j++){
    for(int i=cols-1;i>0;i--){
if(array[i][j]!=0&&array[i][j]==array[i-1][j]){
            return 0;
        }
    }
}
return 1;
}
void Right(int rows, int cols ,int **array){
    for(int a=0;a<rows;a++){
    for(int i=0;i < cols; i++){
    for(int j=0;j<rows-1;j++){
        if(array[i][j]!=0&&array[i][j+1]==0){
            array[i][j+1]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
  //  printf("before combine\n");
//printGameState(rows,cols,array);
  //  printf("\n\n");
    for(int i=0;i < cols; i++){
    for(int j=rows-1;j>0;j--){
if(array[i][j]!=0&&array[i][j]==array[i][j-1]){
            int num = array[i][j]*2;
            array[i][j]=num;
            array[i][j-1]=0;
        }
    }
}
    for(int a=0;a<rows;a++){
    for(int i=0;i < cols; i++){
    for(int j=0;j<rows-1;j++){
        if(array[i][j]!=0&&array[i][j+1]==0){
            array[i][j+1]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
spawnNum(rows,cols,array);
}

void Left(int rows, int cols ,int **array){
    for(int a=0;a<rows;a++){
    for(int i=0;i < cols; i++){
    for(int j=rows-1;j>0;j--){
        if(array[i][j]!=0&&array[i][j-1]==0){
            array[i][j-1]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
  //  printf("before combine\n");
//printGameState(rows,cols,array);
 //   printf("\n\n");
    for(int i=0;i < cols; i++){
    for(int j=0;j<rows-1;j++){
if(array[i][j]!=0&&array[i][j]==array[i][j+1]){
            int num = array[i][j]*2;
            array[i][j]=num;
            array[i][j+1]=0;
        }
    }
}
    for(int a=0;a<rows;a++){
    for(int i=0;i < cols; i++){
    for(int j=rows-1;j>0;j--){
        if(array[i][j]!=0&&array[i][j-1]==0){
            array[i][j-1]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
spawnNum(rows,cols,array);
}
void Up(int rows, int cols ,int **array){
    for(int a=0;a<cols;a++){
    for(int j=0;j < rows; j++){
    for(int i=cols-1;i>0;i--){
        if(array[i][j]!=0&&array[i-1][j]==0){
            array[i-1][j]=array[i][j];
            array[i][j]=0;
        }
    }
}
}
   // printf("before combine\n");
//printGameState(rows,cols,array);
    //printf("\n\n");
    for(int j=0;j < rows; j++){
    for(int i=0;i<cols-1;i++){
if(array[i][j]!=0&&array[i][j]==array[i+1][j]){
            int num = array[i][j]*2;
            array[i][j]=num;
            array[i+1][j]=0;
        }
    }
}
    for(int a=0;a<cols;a++){
    for(int j=0;j < rows; j++){
    for(int i=cols-1;i>0;i--){
        if(array[i][j]!=0&&array[i-1][j]==0){
            array[i-1][j]=array[i][j];
            array[i][j]=0;
        }
    }
}
}
spawnNum(rows,cols,array);
}
void Down(int rows, int cols ,int **array){
    for(int a=0;a<cols;a++){
    for(int j=0;j < rows; j++){
    for(int i=0;i<cols-1;i++){
        if(array[i][j]!=0&&array[i+1][j]==0){
            array[i+1][j]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
        for(int j=0;j < rows; j++){
    for(int i=cols-1;i>0;i--){
if(array[i][j]!=0&&array[i][j]==array[i-1][j]){
            int num = array[i][j]*2;
            array[i][j]=num;
            array[i-1][j]=0;
        }
    }
}

    for(int a=0;a<cols;a++){
    for(int j=0;j < rows; j++){
    for(int i=0;i<cols-1;i++){
        if(array[i][j]!=0&&array[i+1][j]==0){
            array[i+1][j]=array[i][j];
            array[i][j]=0;
        }
    }
}
    }
    spawnNum(rows,cols,array);
}
int main(void){
    srand(time(NULL));
    int rows=0;
    int columns=0;

    printf("How many rows\n");
    scanf("%d",&rows);  
    printf("rows:%d\n",rows);
    printf("how many columns\n");
    scanf("%d",&columns);
    printf("columns:%d\n",columns);
int **Board = malloc(sizeof(int *)*columns);
    if(Board == NULL){
        printf("malloc is fucked");
        return 1;
    }
    resetGameState(rows,columns,Board);
spawnNum(rows,columns,Board);
spawnNum(rows,columns,Board);
//printf("Status %d \n",Status);
while (1 == 1)
{
    char input;
    int X,Y;
    int R,L,U,D;
    int EmptySpaces = findNumEmpty(rows,columns,Board);
    X=0;
    Y=0;
    if(EmptySpaces==0){
         X = CheckHorizontal(rows,columns,Board);
        Y = CheckVertical(rows,columns,Board);
    }

    if(X==1&&Y==1){
        printf("GAME OVER\n");
            printGameState(rows,columns,Board);
            break;
    }
clearScreen();    //if you want to use a debugger comment this out
    printf("\n\n");
            printGameState(rows,columns,Board);
            input = getch();
           // printf("input:%d\n",input);
        if(input =='d'&&X==0){
            R=CheckRight(rows,columns,Board);
            X=CheckHorizontal(rows,columns,Board);
            if(R==1&&X==1){
                printf("Invalid move\n");
                continue;
            }
            Right(rows,columns,Board);
        } 
        if(input =='a'&&X==0){
            L=CheckLeft(rows,columns,Board);
            X=CheckHorizontal(rows,columns,Board);
            if(L==1&&X==1){
                printf("Invalid move\n");
                continue;
            }
            Left(rows,columns,Board);
        }
        if(input =='s'&&Y==0){
            D=CheckDown(rows,columns,Board);
            Y=CheckVertical(rows,columns,Board);
            if(D==1&&Y==1){
                printf("Invalid move\n");
                continue;
            }
            Down(rows,columns,Board);
        }
        if(input =='w'&&Y==0){
            U=CheckUp(rows,columns,Board);
            Y=CheckVertical(rows,columns,Board);
            if(U==1&&Y==1){
                printf("Invalid move\n");
                continue;
            }
            Up(rows,columns,Board);
        }
        if(input =='e'){
           int Status = spawnNum(rows,columns,Board);
           printf("status :%d\n",Status);
        }
        if(input == 27){
           printf("Quitting\n");
           break;
        }
        
      //  findBlockCords(rows,columns,GameState,pCordArray);
}

free(Board);
Board=NULL;

return 0;
}