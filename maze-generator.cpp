#include<iostream>
#include<vector>
#include<sstream>
#include<cstdlib>

using namespace std;

int xsize,ysize;
vector<vector<int> > maze;

int countvisited=0;
vector<vector<bool> > visited;

void check(int x, int y)
{
	if(maze[x][y]==1)
		return;
	if(visited[x][y])
		return;

	visited[x][y]=true;
	countvisited++;
	
	check(x-1,y);
	check(x+1,y);
	check(x,y-1);
	check(x,y+1);
}

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		cerr << "Maze Generator: generates a random maze." << endl;
		cout << "Syntax:" << argv[0] << " " << "xsize ysize" << endl;
		exit(1); 
	}

	srand(time(0));

	stringstream xsizearg(argv[1]);
	stringstream ysizearg(argv[2]);	
	
	xsizearg >> xsize;
	ysizearg >> ysize;

	if(xsize < 3 || ysize < 3)
		return 1;

	
	int countfree;
	int xbegin,ybegin;
	do{
		cerr << ".";
		xbegin=-1;
		ybegin=-1;
		countfree = 0;
		countvisited = 0;
		maze.clear();
		maze.resize(xsize,vector<int>(ysize,0));
		visited.clear();
		visited.resize(xsize,vector<bool>(ysize,false));

		for(int x=0;x<xsize;x++)
		{
			maze[x][0] = 1;
			maze[x][ysize-1] = 1;
		}

		for(int y=0;y<ysize;y++)
		{
			maze[0][y] = 1;
			maze[xsize-1][y] = 1;
		}

		for(int x=1;x<xsize-1;x++)
			for(int y=1;y<ysize-1;y++)
			{
				if(!( (x==1&&y==1) || (x==xsize-2&&y==ysize-2)) && random()%1000 <= 450)
					maze[x][y] = 1;
				else
				{
					countfree++;
					if(xbegin==-1)
					{
						xbegin=x;
						ybegin=y;
					}
				}
			}

		check(xbegin,ybegin);
		//cerr << countvisited << " " << countfree << endl;
	} while(countvisited < countfree);

	cout << endl;
	cout << xsize << " " << ysize << endl;

	for(int y=0;y<ysize;y++)
	{
		for(int x=0;x<xsize;x++)
			cout << maze[x][y] << " ";
		cout << endl;
	}

	cout << xbegin << " " << ybegin << endl;
	return 0;
}
