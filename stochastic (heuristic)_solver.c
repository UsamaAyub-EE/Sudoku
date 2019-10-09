#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
short matrix[81],indices[50],count=0,i,j,access[9][9][10];
void make_access();
void empty();
int rep_check();
void add_row();
void print_access();
short get_place();
void make_sudoku(int);
void fill_row();
int check_index(int);
void print_matrix(char);
int check_row(int);
int check_column(int);
int check_box(int);
void get_sudoku();
int main()
{
	srand(time(NULL));
	char choice;
	int total_index,cycles=0;
	short int place=1;
	puts("Do you wish to enter the sudoku puzzle yourself or use a randomly "
	"generated puzzle? Enter 1 for first choice and 2 for second choice.");
	scanf("%c",&choice);
	if(choice==49)
		get_sudoku();
	else if(choice==50)
	{
		puts("Enter how many indices you wish to be filled in random puzzle");
		scanf("%d",&total_index);
		make_sudoku(total_index);
	}
	else
		return 0;
	/*
	matrix[20]=1;indices[0]=20;
	matrix[22]=2;indices[1]=22;
	matrix[14]=3;indices[2]=14;
	matrix[16]=8;indices[3]=16;
	matrix[17]=5;indices[4]=17;
	matrix[46]=9;indices[5]=46;
	matrix[38]=4;indices[6]=38;
	matrix[30]=5;indices[7]=30;
	matrix[32]=7;indices[8]=32;
	matrix[42]=1;indices[9]=42;
	matrix[54]=5;indices[10]=54;
	matrix[65]=2;indices[11]=65;
	matrix[67]=1;indices[12]=67;
	matrix[76]=4;indices[13]=76;
	matrix[61]=7;indices[14]=61;
	matrix[62]=3;indices[15]=62;
	matrix[80]=9;indices[16]=80;
	count=17;
	*/
	puts("The sudoku puzzle to solve is as under:\n");
	print_matrix(50);
	make_access();
	//puts("The accesses are as under:\n");
	//print_access();
	i=j=0;
	fill_row();
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			if(++cycles==500000)
			{
				puts("No solution");
				return 0;
			}
			if(check_index(9*i+j))
				continue;
			//if(matrix[9*i+j]!=0)
			//	continue;
			place=matrix[9*i+j];
			matrix[9*i+j]=0;
			if(check_row(place)==0&&check_column(place)==0&&check_box(place)==0)
			{
				matrix[9*i+j]=place;
				continue;
			}
			else
			{
				fill_row();
				//print_matrix(50);
			}
		}
	}
	puts("The solution is as under:\n");
	print_matrix(50);
	return 0;
}
void print_matrix(char ch)
{
	int i,j;
	for(i=0;i<9;i++)
	{
		if(i%3==0)
			puts("---------------------------");
		for(j=0;j<9;j++)
		{
			if(j%3==0)
				printf(" |");
			if(ch==48)
			{
				printf("%3d",9*i+j+1);
				continue;
			}
			if(matrix[9*i+j]==0)
				printf("  ");
			else
				printf("%2d",matrix[9*i+j]);
		}
		puts(" |");
	}
	puts("---------------------------");
}
void get_sudoku()
{
	char chr='n';
	int p=1,n;
	puts("Below is printed the sudoku matrix with indices instead of "
	"the numbers.Enter the corresponding indices for the locations where"
	" you wish to enter any number");
	print_matrix(48);
	puts("Do you wish to see the sudoku as you enter the numbers.Enter y if yes."
	"Else press any key");
	scanf("%c",&chr);
	scanf("%c",&chr);
	while(p!=100)
	{
		puts("Enter the index. Enter 100 to stop entering");
		scanf("%d",&p);
		if(p==100)
		break;
		while(p<1||p>81)
		{
			puts("You entered invalid index.Please enter valid index");
			scanf("%d",&p);
		}
		puts("Enter the number at this index");
		scanf("%d",&n);
		while(n>9||n<1)
		{
			puts("The number at any index must lie between 1 and 9."
			"Please enter a valid number:");
			scanf("%d",&n);
		}
		j=(p-1)%9;
		i=(p-1-j)/9;
		if(check_row(n))
		{
			puts("This number at this index is not possible as row "
			"constraint will be violated.");
			continue;
		}
		if(check_column(n))
		{
			puts("This number at this index is not possible as column "
			"constraint will be violated.");
			continue;
		}
		if(check_box(n))
		{
			puts("This number at this index is not possible as box "
			"constraint will be violated.");
			continue;
		}
		matrix[p-1]=n;
		indices[count++]=p-1;
		if(chr=='y'||chr=='Y')
		{
			puts("The sudoku puzzle you have entered so far is as under\n");
			print_matrix(50);
		}
		if(count%5==0)
		{
			puts("The matrix with indices is as under:");
			print_matrix(48);
		}
	}
}
int check_row(int num)
{
	int p;
	for(p=0;p<9;p++)
	{
		if(matrix[9*i+p]==num)
			return 1;
	}
	return 0;
}
int check_column(int num)
{
	int p;
	for(p=0;p<9;p++)
	{
		if(matrix[9*p+j]==num)
			return 1;
	}
	return 0;
}
int check_box(int num)
{
	int a,b;
	if(i>=0&&i<=2)
		a=0;
	else if(i>=3&&i<=5)
		a=3;
	else
		a=6;
	if(j>=0&&j<=2)
		b=0;
	else if(j>=3&&j<=5)
		b=3;
	else
		b=6;
	short int p,q;
	for(p=a;p<a+3;p++)
	{
		for(q=b;q<b+3;q++)
		{
			if(matrix[9*p+q]==num)
				return 1;
		}
	}
	return 0;
}
int check_index(int indx)
{
	int p;
	for(p=0;p<count;p++)
	{
		if(indices[p]==indx)
			return 1;
	}
	return 0;
}
void make_sudoku(int total_index)
{
	if(count==total_index)
		return;
	else
	{
		short int place,index,counter=0;
		index=rand()%81;
		j=(index)%9;
		i=(index-j)/9;
		while(1)
		{
			place=1+rand()%9;
			if(++counter==30)
				break;
			if(check_row(place)==0&&check_column(place)==0&&check_box(place)==0&&check_index(index)==0)
			{
				matrix[index]=place;
				indices[count++]=index;
				break;
			}
		}
		make_sudoku(total_index);
	}
}
void make_access()
{
	short place=1,k;
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			for(k=0,place=1;place<10;++place)
			{
				if(check_row(place)==0&&check_column(place)==0&&check_box(place)==0)
				{
					access[i][j][k++]=place;
				}
			}
			access[i][j][k]=-1;
		}
	}
}
/*
void print_access()
{
	short i,j,k;
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			printf("At i=%d and j=%d :- ",i,j);
			for(k=0;;++k)
			{
				if(access[i][j][k]==-1)
					break;
				printf("%2d,",access[i][j][k]);
			}
			puts("");
		}
	}
}
*/
void fill_row()
{
	static short row_count;
	short place,counter=0;
	for(j=0;j<9;++j)
	{
		if(check_index(9*i+j))
			continue;
		matrix[9*i+j]=0;
	}
	for(j=0;j<9;++j)
	{
		if(counter==20)
		{
			break;
		}
		if(check_index(9*i+j))
			continue;
		place=get_place();
		if(check_row(place)==0&&check_column(place)==0&&check_box(place)==0)
		{
			matrix[9*i+j]=place;
			counter=0;
		}
		else
		{
			++counter;
			--j;
		}
	}
	if(row_count>=20)
	{
		/*for(j=0;j<9;++j)
		{
			if(check_index(9*i+j))
				continue;
			matrix[9*i+j]=0;
		}*/
		row_count=0;
		//empty();
		if(i==0)
		{
			empty();
		}
		else
		{
			--i;
		}
		fill_row();
	}
	if(counter==20)
	{
		++row_count;
		fill_row();
	}
	//print_matrix(50);
}
short get_place()
{
	short size;
	for(size=0;;++size)
	{
		if(access[i][j][size]==-1)
			break;
	}
	return access[i][j][rand()%size];
}
void empty()
{
	short i;
	for(i=0;i<81;i++)
	{
		if(check_index(i))
			continue;
		matrix[i]=0;
	}
}
