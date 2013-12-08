#include<iostream>
#include<vector>
#include<sstream>
#include<cstdlib>

using namespace std;

int xsize,ysize,zsize;
vector<vector<vector<int> > > maze;

int countvisited=0;
vector<vector<vector<bool> > > visited;

void check(int x, int y, int z)
{
	if(maze[x][y][z]==1)
		return;
	if(visited[x][y][z])
		return;

	visited[x][y][z]=true;
	countvisited++;
	
	check(x-1,y,z);
	check(x+1,y,z);
	check(x,y-1,z);
	check(x,y+1,z);

	check(x,y,z-1);
	check(x,y,z+1);
}

int main(int argc,char **argv)
{
	if(argc!=4)
	{
		cerr << "Maze Generator: generates a random 3D maze." << endl;
		cout << "Syntax:" << argv[0] << " " << "xsize ysize zsize" << endl;
		exit(1); 
	}

	srand(time(0));

	stringstream xsizearg(argv[1]);
	stringstream ysizearg(argv[2]);	
	stringstream zsizearg(argv[3]);	
	
	xsizearg >> xsize;
	ysizearg >> ysize;
	zsizearg >> zsize;

	if(xsize < 3 || ysize < 3 || zsize < 3)
		return 1;

	
	int countfree;
	int xbegin,ybegin, zbegin;
	do{
		cerr << ".";
		xbegin=-1;
		ybegin=-1;
		zbegin=-1;
		countfree = 0;
		countvisited = 0;
		maze.clear();
		maze.resize(xsize,vector<vector<int> >(ysize,vector<int>(zsize,0)));
		visited.clear();
		visited.resize(xsize,vector<vector<bool> >(ysize,vector<bool>(zsize,false)));

//		cerr << "check1" << endl;
		for(int x=0;x<xsize;x++)
			for(int y=0;y<ysize;y++)
				for(int z=0;z<zsize;z++)
				{
					if( (x==0||x==xsize-1) || (y==0 ||y==ysize-1) || (z==0||z==zsize-1) )
					{
//						cerr << x << "," << y << "," << z << endl;
						maze[x][y][z]=1;
					}
				}
//		cerr << "check2" << endl;
		for(int x=1;x<xsize-1;x++)
			for(int y=1;y<ysize-1;y++)
				for(int z=1;z<zsize-1;z++)
				{
					if(!( (x==1&&y==1&&z==1) || (x==xsize-2&&y==ysize-2&&z==zsize-2)) && random()%1000 <= 750)
					{
//						cerr << x << "," << y << "," << z << endl;
						maze[x][y][z] = 1;
					}
				else
				{
					countfree++;
					if(xbegin==-1)
					{
						xbegin=x;
						ybegin=y;
						zbegin=z;
					}
				}
			}

		check(xbegin,ybegin,zbegin);
		//cerr << countvisited << " " << countfree << endl;
	} while(countvisited < countfree);

	cout << endl;
	cout << xsize << " " << ysize << " " << zsize << endl;

	for(int z=0;z<zsize;z++)
	{
		for(int y=0;y<ysize;y++)
		{
			for(int x=0;x<xsize;x++)
				cout << maze[x][y][z] << " ";
			cout << endl;
		}
		cout << endl << endl;
	}

	cout << xbegin << " " << ybegin << " " << zbegin << endl;
	return 0;
}
