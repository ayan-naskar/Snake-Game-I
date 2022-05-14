#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

void initializezero(int *p)
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			*(p+j+10*i)=0;
}

void show(int *p,int head)
{
	int i,j;
	printf("# # # # # # # # # # # #\n");
	for(i=0;i<10;i++)
	{
		printf("#");
		for(j=0;j<10;j++)
		{	
			/*if(x==i && y==j)
				printf(" @");
			else if(*(p+j+5*i)==0)
				printf(" x");
			else if(*(p+j+5*i)==2)
				printf("  ");}*/
			if(*(p+j+10*i)==0)
				printf("  ");
			else
			{
				if(*(p+j+10*i)!=-1)
					if(*(p+j+10*i)==head)
						printf(" O");
					else
						printf(" o");
				else
					printf(" X");
			}
		}
		printf(" #\n");
	}//printf("w");
	printf("# # # # # # # # # # # #\n");
}

int gettimert()
{
	int x=500;
	char a,b;
	while(1)
	{
		system("cls");
		printf("Select the time for which the snake can live without choking\n");
		printf("<%d millisecs>",x);
		click:a=getch();
		if(a==13)
		{
			return x;
		}
		else if(a==-32)
		{
			b=getch();
			if(b==75)
				x-=500;
			else if(b==77)
				x+=500;

			if(x==0)
			{
				x=500;
				printf("\nTime cannot be 0");
				goto click;
			}
		}
	}
}

int main()
{
	FILE *f;
	int timer;
	clock_t start,end;
	int arr[100],i,j,trv,oldhihead;
	int head=1;
	srand(time(0));
	char key,key2;
	int x=5,y=5;
	int points=0;
	i=(int)rand()%10;
	j=(int)rand()%10;
	//printf("%d %d",i,j);
	initializezero(arr);
	arr[10*x+y]=1;
	arr[10*i+j]=-1;
	timer=gettimert();
	system("cls");
	printf("Press any key to start");
	key=getch();
	if(key==-32)
	key=getch();
	while(1)
	{
		start=clock();
		//printf("\f");
		system("cls");
		printf("WORST SNAKE GAME EVER\n");
		printf("~~~~~~~~~~~~~~~~~~~~~\n\n");
		show(arr,head);
		key=getch();
		key2=getch();
		//arr[10*x+y]=0;
		if(key==-32 && key2==72)
			x--;
		else if(key==-32 && key2==80)
			x++;
		else if(key==-32 && key2==77)
			y++;
		else if(key==-32 && key2==75)
			y--;
		if(x<0)
			x=9;
		if(y<0)
			y=9;
		x%=10;
		y%=10;
		
		for(trv=0;trv<100;trv++)
		{
			if(arr[trv]>0)
				arr[trv]--;
		}
		if(x==i && y==j)
		{
			arr[10*i+j]=++head;			
			i=rand()%10;
			j=rand()%10;
			points++;
			arr[10*i+j]=-1;
			goto there;
		}
		if(arr[10*x+y]>0)
		{
			system("cls");
			printf("GAME OVER!!");
			printf("\n~~~~~~~~~~~\n\n");
			show(arr,head);			
			printf("\nYour snake ate itself!");
			printf("\nYour Score is: %d",head);
			goto thatplace;
		}

		arr[10*x+y]=head;
		end=clock();
		there:if(end-start>1000.0)
		{
			system("cls");
			printf("GAME OVER!!");
			printf("\n~~~~~~~~~~~\n\n");
			show(arr,head);
			printf("\nYour snaked choked to death. Please try to instruct the snake faster!");
			printf("\nYour Score is: %d",head);
			goto thatplace;
		}
	}
	thatplace:f=fopen("Scoreboard.txt","r");
	if(f==NULL)
	{
		f=fopen("Scoreboard.txt","w");
		fprintf(f,"%d",head);
		printf("\nThis is your new high score: %d",head);
		fclose(f);
	}
	else
	{
		fscanf(f,"%d",&oldhihead);
		if(head>oldhihead)
		{
			printf("\nThis is your new high score: %d",head);
			fprintf(f,"%d",head);
		}
		else
		{
			printf("\nYour old Best Score ever was: %d",oldhihead);
		}
		fclose(f);
	}
	for(i=0;i<1000000;i++)printf("");
	printf("\n\n\nPress any key to continue");
	key=getch();
	if(key==-32)
		getch();
	system("Justagame.exe 5434 localhost");
}
