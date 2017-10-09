/******************************************************************************
*                                                                             *
*   Get Sudoku 1.0 - The free portable interactive sudoku solver              *
*   Copyright (C) 2007    Nedeljko Stefanovic  (e-mail: stenedjo@yahoo.com)   *
*                                                                             *
*   This program is free software; you can redistribute it and/or modify      *
*   it under the terms of the GNU General Public License as published by      *
*   the Free Software Foundation; either version 2 of the License, or         *
*   (at your option) version 3.                                               *
*                                                                             *
*   This program is distributed in the hope that it will be useful,           *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*   GNU General Public License for more details.                              *
*                                                                             *
*   You should have received a copy of the GNU General Public License along   *
*   with this program; if not, write to the Free Software Foundation, Inc.,   *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
*                                                                             *
******************************************************************************/


#ifndef SUDOKU_H
#define SUDOKU_H

#define NO_VALUE 9

#include <iostream>


using namespace std;


class Sudoku
{
    int possibilities_in_field[9][9];
    int possibilities_in_row[9][9];
    int possibilities_in_column[9][9];
    int possibilities_in_block[9][9];
    bool possible_value[9][9][9];
	int known_value[9][9];
	int given_value[9][9];

	void clean();
	void set(int,int,int);
	void reset(int,int,int);

public:

    Sudoku();
    Sudoku(const Sudoku &);
    Sudoku & operator=(const Sudoku &);
    bool operator==(const Sudoku &) const;
    bool operator!=(const Sudoku &) const;
	void give(int,int,int);
	void remove(int,int);
	void solve();
	void find_all_possibilities();
	int given(int,int) const;
	int known(int,int) const;
	bool possible(int,int,int) const;
	void read(istream &);
	void write(ostream &) const;
};

istream & operator>>(istream&, Sudoku&);
ostream & operator<<(ostream&, const Sudoku&);

extern Sudoku solver;

#endif
