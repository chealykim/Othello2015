// Maze_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>
#include<stdio.h>
#include<conio.h>
#include <string>
#include <iostream>
#include <fstream>

// srand, rand funtions are available in stdlib.h
////v1 = rand() % 100; // v1 in the range 0 to 99
////v2 = rand() % 100 + 1; // v2 in the range 1 to 100
////v3 = rand() % 30 + 1985; // v3 in the range 1985-2014

using namespace std;

struct Cell {
	char row;
	char col;
};

struct shortestPathStkDFS {
	stack<Cell> dfsPath;
};

void dfs(char row, char col, char Array[17][17]) {
	int East=0, West=0, North=0, South=0, count=0;
	char nbRowNorth, nbRowSouth;
	char nbColEast, nbColWest, direction;
	nbRowNorth = row - 2;	//North Neighbor
	nbRowSouth = row + 2;	//South Neighbor
	nbColEast  = col + 2;	//East  Neighbor
	nbColWest  = col - 2;	//West  Neighbor
	direction = rand() % 4;    //4 + 0 -1 = 3 (from 0 to 3)
	Array[row][col] = ' ';
	//East = 0, West=1, North=2, South=3;
	while (count != 4) {
		//nbColEast  = col + 2;	//East  Neighbor
		if ((direction == 0) && (East==0)) { 		//East 
			East = 1;
			if ((nbColEast > 16) || (Array[row][nbColEast] == ' ')) {
				count++;
			}
			else if ((nbColEast < 16) && (Array[row][nbColEast] == '*')) {
				Array[row][col + 1] = ' ';
				dfs(row, nbColEast, Array);
				count++;
			}
		}
		//nbColWest  = col - 2;	//West  Neighbor
		else if ((direction == 1) && (West == 0)) { 	//West
			West = 1;
			if ((nbColWest < 0) || ((Array[row][nbColWest]) == ' ')) {
				count++;
			}
			else if ((nbColWest > 0) && (Array[row][nbColWest] == '*')) {
				Array[row][col - 1] = ' ';
				dfs(row, nbColWest, Array);
				count++;
			}
		}
		//nbRowNorth = row - 2;	//North Neighbor
		else if ((direction == 2) && (North == 0)) { //Norht
			North = 1;
			if ((nbRowNorth < 0) || (Array[nbRowNorth][col] == ' ')) {
				count++;
			}
			else if ((nbRowNorth > 0) && (Array[nbRowNorth][col ] == '*')) {
				Array[row - 1][col] = ' ';
				dfs(nbRowNorth, col,  Array);
				count++;
			}
		}
		//nbRowSouth = row + 2;	//South Neighbor
		else if ((direction == 3) && (South == 0)) { //South
			South = 1;
			if ((nbRowSouth > 16) || (Array[nbRowSouth][col] == ' ')) {
				count++;
			}
			else if ((nbRowSouth < 16) && (Array[nbRowSouth][col] == '*')) {
				Array[row  + 1][col] = ' ';
				dfs(nbRowSouth, col, Array);
				count++;
			}
		}
		direction = rand() % 4;
	}
}

shortestPathStkDFS traversalDFS(char row, char col, char Array[17][17]) {
	char mazeGoal = 0;
	char  noWall = 1;
	char rowNorthWall=0, rowSouthWall=0;
	char colEastWall=0, colWestWall=0;
	rowNorthWall = row - 1;	//North Wall
	rowSouthWall = row + 1;	//South Wall
	colEastWall = col + 1;	//East  Wall
	colWestWall = col - 1;	//West  Wall

	shortestPathStkDFS stackStruct;
	Cell vistdCell;
	stack<Cell> stkDFS;
	vistdCell.row = row;
	vistdCell.col = col;
	Array[vistdCell.row][vistdCell.col] = 'v';	
	stkDFS.push(vistdCell);
	while (mazeGoal != 'G') {
		row = vistdCell.row;
		col = vistdCell.col;
		while (noWall == 1) {
			if (Array[vistdCell.row][vistdCell.col] == 'G') {
				mazeGoal = 'G';
				noWall = 0;
				while (!stkDFS.empty()) {
					vistdCell.row = stkDFS.top().row;
					vistdCell.col = stkDFS.top().col;
					//Array[vistdCell.row][vistdCell.col] = 'M';
					stackStruct.dfsPath.push(vistdCell);
					stkDFS.pop();
				}
			}
			else if (Array[vistdCell.row][vistdCell.col] == ' ') {
				Array[vistdCell.row][vistdCell.col] = 'v';
				stkDFS.push(vistdCell);
				row = vistdCell.row;
				col = vistdCell.col;
			}
			rowNorthWall = row - 1;	//North Wall
			rowSouthWall = row + 1;	//South Wall
			colEastWall = col + 1;	//East  Wall
			colWestWall = col - 1;	//West  Wall
			//Fourth: Traverse SOUTH
			if ((Array[rowSouthWall][col] == ' ') && 
				(Array[rowSouthWall + 1][col] != 'v')) {//Either ' ' or 'G'
				vistdCell.row = rowSouthWall + 1;
				vistdCell.col = col;
			}
			//Second: Traverse WEST
			else if ((Array[row][colWestWall] == ' ') && 
				(Array[row][colWestWall - 1] != 'v')) {//Either ' ' or 'G'
				vistdCell.row = row;
				vistdCell.col = colWestWall - 1;
			}

			//Third: Traverse NORTH
			else if ((Array[rowNorthWall][col] == ' ') && 
				(Array[rowNorthWall - 1][col] != 'v')) {//Either ' ' or 'G'
				vistdCell.row = rowNorthWall - 1;
				vistdCell.col = col;
			}
			//First: Traverse EAST 
			else if ((Array[row][colEastWall] == ' ') && 
				(Array[row][colEastWall + 1] != 'v')) { //Either ' ' or 'G'
				vistdCell.row = row;
				vistdCell.col = colEastWall + 1;
			}
			else
				noWall = 0;
		}
		if (!stkDFS.empty()) {
			stkDFS.pop();
			vistdCell.row = stkDFS.top().row;
			vistdCell.col = stkDFS.top().col;
			noWall = 1;
		}
	}	
	return stackStruct;
}

int main() {

	srand(time(NULL));
	char Array[17][17];
	char arrayReOpen[17][17];
	char ArrayStruct[17][17];
	int line = 1, ii = 0, jj = 0;
	int row = 0, col = 0;
	ofstream mazeArray;
	mazeArray.open("theMaze.txt");
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (((i % 2) == 0) && ((j % 2) != 0)) {
				Array[i][j] = '-';
			}
			else if (((i % 2) != 0) && ((j % 2) != 0)) {
				Array[i][j] = '*';
			}
			else
				Array[i][j] = '|';
		}
	}
	int roww = 0, coll = 0;
	if (roww % 2 == 0) {
		while (roww % 2 == 0)
			roww = rand() % 17;
	}
	if (coll % 2 == 0) {
		while (coll % 2 == 0)
			coll = rand() % 17;
	}
	dfs(roww, coll, Array);

	cout << "Print out the dfs Array: " << endl;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if ((i == 1) && (j == 15))
				Array[i][j] = 'G';
			ArrayStruct[i][j] = Array[i][j];
			cout << Array[i][j];
			mazeArray << Array[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				mazeArray << "\n";
				line = 1;
			}
		}
	}
	mazeArray.close();
	cout << endl;
	shortestPathStkDFS dfsPathStruct;

	dfsPathStruct = traversalDFS(15, 1, Array);
	cout << "Micro Mouse Initial Rout:  " << endl;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << Array[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}
	cout << endl;
	row = dfsPathStruct.dfsPath.top().row;
	col = dfsPathStruct.dfsPath.top().col;
	Array[row][col] = 'M';
	dfsPathStruct.dfsPath.pop();
	cout << "Micro Mouse Second Rout: " << endl;
	for (int i = 0; i < 17; i++) { 
		for (int j = 0; j < 17; j++) {
			cout << Array[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}	
	while (!dfsPathStruct.dfsPath.empty()) {
		row = dfsPathStruct.dfsPath.top().row;
		col = dfsPathStruct.dfsPath.top().col;
		Array[row][col] = 'M';
		dfsPathStruct.dfsPath.pop();
		cout << "Micro mouse next rout: " << endl;
		cin.get();
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				cout << Array[i][j];
				line++;
				if (line == 18) {
					cout << endl;
					line = 1;
				}
			}
		}		
	}
	cout << endl;
	string rowString;
	ifstream myfile("theMaze.txt");
	if (myfile.is_open()) {
		while (getline(myfile, rowString))
		{
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
					arrayReOpen[i][j] = rowString[j];
				}
				getline(myfile, rowString);
			}
		}
	}

	cout << "Open previous maze: " << endl;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << arrayReOpen[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}
	int r=1, c=2;
	if (arrayReOpen[r][c] == ' ')
		arrayReOpen[r][c] = '|';
	else if (arrayReOpen[r][c] == '|')
		arrayReOpen[r][c] = ' ';

	 r = 7, c = 10;
	if (arrayReOpen[r][c] == ' ')
		arrayReOpen[r][c] = '|';
	else if (arrayReOpen[r][c] == '|')
		arrayReOpen[r][c] = ' ';

	r = 7, c = 2;
	if (arrayReOpen[r][c] == ' ')
		arrayReOpen[r][c] = '|';
	else if (arrayReOpen[r][c] == '|')
		arrayReOpen[r][c] = ' ';

	r = 14, c = 15;
	if (arrayReOpen[14][15] == ' ')
		arrayReOpen[14][15] = '-';
	else if (arrayReOpen[14][15] == '-')
		arrayReOpen[14][15] = ' ';

	if (arrayReOpen[4][15] == ' ')
		arrayReOpen[4][15] = '-';
	else if (arrayReOpen[4][15] == '-')
		arrayReOpen[4][15] = ' ';

	cout << "Modified maze: " << endl;
	cin.get();
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << arrayReOpen[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}

	dfsPathStruct = traversalDFS(15, 1, arrayReOpen);
	cout << "Micro Mouse Initial Modified Rout:  " << endl;
	cin.get();
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << arrayReOpen[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}
	cout << endl;
	row = dfsPathStruct.dfsPath.top().row;
	col = dfsPathStruct.dfsPath.top().col;
	arrayReOpen[row][col] = 'M';
	dfsPathStruct.dfsPath.pop();

	while (!dfsPathStruct.dfsPath.empty()) {
		row = dfsPathStruct.dfsPath.top().row;
		col = dfsPathStruct.dfsPath.top().col;
		arrayReOpen[row][col] = 'M';
		dfsPathStruct.dfsPath.pop();
	}
	cout << "Micro mouse Modified Rout: " << endl;
	cin.get();
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << arrayReOpen[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}
	cout << endl;
	cout << "Micro Mouse previous Rout: " << endl;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << Array[i][j];
			line++;
			if (line == 18) {
				cout << endl;
				line = 1;
			}
		}
	}	
	return 0;
}