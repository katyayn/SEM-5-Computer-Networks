#include<stdio.h>
#include<iostream>
#include<process.h>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<dos.h>

using namespace std;

int row=0, column=0, road_flag=1;

int working_matrix[100][100]={0};

////////////////////////////////////////////////
//RSU Declarations Start////////////////////////
////////////////////////////////////////////////


int change_matrix[100][100]={0};
int max_i=0,max_j=0,max_count=0,road_units_left=0, number_of_road_units=0;




void input_matrix();
void create_road(int,int,int,int);
void enter_road();
void display_matrix();
void count_road_units();


void place_RSU();
void display_change_matrix();
void copy_matrix();
void run_count_matrix_once();






/////////////////////////////////////////////////
//creating road starts here//////////////////////
/////////////////////////////////////////////////



void input_matrix()
{
	cout<<"\n\n\t\tEnter the number of rows(upto 100):\t";
	cin>>row;

	cout<<"\n\n\t\tEnter the number of columns(upto 100):\t";
	cin>>column;

	display_matrix();

	cout<<"\n\n\t Lets make a road\n" ;

	while(road_flag)
	{
		enter_road();
	}

	cout<<"\n\n\tThe following is the layout:\n";

	display_matrix();

}



void display_matrix()
{
	cout<<"\n\nThe following is your matrix:\n\n";


	cout<<" \t";
	for(int i=0;i<column;i++)
	{
		cout<<i+1<<"\t";
	}

	cout<<"\n\n";

	for(int i=0;i<row;i++)
	{

		cout<<i+1<<"\t";

		for(int j=0;j<column;j++)
		{
			cout<<working_matrix[i][j]<<"\t";
		}

		cout<<"\n\n";
	}
}




void create_road(int start_x,int start_y,int end_x,int end_y)
{
	int i,j;

	if(start_x>end_x || start_y>end_y)
	{
		for(i=end_x-1;i<start_x;i++)
		{
			for(j=end_y-1;j<start_y;j++)
			{
				working_matrix[i][j]=99;
			}
		}
	}

	for(i=start_x-1;i<end_x;i++)
	{
		for(j=start_y-1;j<end_y;j++)
		{
			working_matrix[i][j]=99;
		}
	}
}


void enter_road()
{
	int road_starting_x,road_ending_x, road_starting_y, road_ending_y;

	cout<<"\n\n\tEnter the coordinates of the starting point:\t";
	scanf("%d,%d",&road_starting_x,&road_starting_y);
	cout<<"\n\n\tEnter the coordinates of the ending point:\t";
	scanf("%d,%d",&road_ending_x,&road_ending_y);

	create_road(road_starting_x,road_starting_y,road_ending_x,road_ending_y);

	display_matrix();

	system("pause");

	cout<<"\n\n\tDo you want to create more road? (1/0):\t";
	cin>>road_flag;

}



void count_road_units()
{
	int i,j;

	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			if(working_matrix[i][j]==99)
			{
				number_of_road_units++;
			}
		}
	}
}


///////////////////////////////////////////////////////
///Placing RSU Starts Here/////////////////////////////
///////////////////////////////////////////////////////





void copy_matrix()
{

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			change_matrix[i][j]=working_matrix[i][j];
		}
	}
}




void display_change_matrix()
{
	cout<<"\n\nThe following is your Changed matrix:\n\n";


	cout<<" \t";
	for(int i=0;i<row;i++)
	{
		cout<<i+1<<"\t";
	}

	cout<<"\n\n";

	for(int i=0;i<row;i++)
	{

		cout<<i+1<<"\t";

		for(int j=0;j<column;j++)
		{
			cout<<change_matrix[i][j]<<"\t";
		}

		cout<<"\n\n";
	}
}





void count_the_matrix(int i, int j)
{
	int current_road_unit_count=0;

	//cout<<"\n\nCOUNT THE MATRIX STARTS for "<<i+1<<","<<j+1<<"\n";

	for(int x=i-1;x<=i+1;x++)
	{
		for(int y=j-1;y<=j+1;y++)
		{
			if(i==row && x==i+1 || i==0 && x==i-1 || j==column && y==j+1 || j==0 && y==j-1)//out of matrix bounds
			{
				//cout<<"\n"<<x+1<<","<<y+1<<"--skipped";
			}


			else
			{
				if(change_matrix[x][y]==99)
	 			{
	 				current_road_unit_count++;

					 //cout<<"\nfound road unit at:\t"<<x+1<<","<<y+1<<"\n---------------current road_unit count for "<<i+1<<","<<j+1<<":\t"<<current_road_unit_count<<"\n-------max count previous:\t"<<max_count<<"\n\n";
	 			}

			}

		}
	}

	if(current_road_unit_count>max_count)
	{
		max_i=i;
		max_j=j;
		max_count=current_road_unit_count;
	}
}





void run_count_matrix_once()
{

    //cout<<"\n\nRUNNNING COUNT MATRIX ONCE:\n\n";

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(working_matrix[i][j]!=99)
			{
				count_the_matrix(i,j);
			}
		}
	}

	//cout<<"\n\ncount max:\t"<<max_count<<"\nmax i:\t"<<max_i+1<<"\nmax j:\t"<<max_j+1<<"\n\n";



}




void update_change_matrix(int i, int j)
{
	for(int x=i-1;x<=i+1;x++)
	{
		for(int y=j-1;y<=j+1;y++)
		{
			if(change_matrix[x][y]==99)
	 		{
	 			change_matrix[x][y]=11;
	 		}

		}
	}

	working_matrix[i][j]=4;
	change_matrix[i][j]=4;

}




void place_RSU()
{
	while(road_units_left!=0)
	{
		run_count_matrix_once();

		for(int i=0;i<row;i++)
		{
			if(max_i==i)
			{

				for(int j=0;j<column;j++)
				{

					//delay(100);
					//system("pause");
					//cout<<"\t"<<i<<"::"<<j<<endl;
					//cout<<"After count once";

					if(max_i==i && max_j==j)
					{
						//cout<<"After if";
						update_change_matrix(i,j);

						road_units_left-=max_count;

						max_count=0;

						display_change_matrix();
						display_matrix();

						//cout<<"\n\n----------------------"<<road_units_left<<"\n\n--------------------------------";

						//system("pause");

					}
				}

			}
		}
	}
}


int main()
{

	input_matrix();

	count_road_units();

	road_units_left=number_of_road_units;


///////////////////////////////////////

	//display_change_matrix();

	//system("pause");

	copy_matrix();

	//system("pause");

	display_change_matrix();

	//system("pause");

	run_count_matrix_once();

	//system("pause");

	display_matrix();

	place_RSU();

	//display_matrix();

	//display_change_matrix();


	return 0;
}
