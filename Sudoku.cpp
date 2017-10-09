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


#include "Sudoku.h"
#include <stdlib.h>


Sudoku solver;

#define LOOP(counter,x)			\
{								\
	int l;						\
	counter = r;				\
								\
	for (l=0; l<9; l++)			\
	{							\
		x;						\
		counter++;				\
								\
		if (counter==9)			\
			counter = 0;		\
	}							\
}

#define BY_FIELD(x)				\
{								\
    int old_k = k;				\
    							\
	LOOP(k,x)          			\
    k = old_k;					\
}

#define BY_ROW(x)				\
{								\
	int old_j = j;				\
								\
	LOOP(j,x)					\
	j = old_j;					\
}

#define BY_COLUMN(x)			\
{								\
	int old_i = i;				\
								\
	LOOP(i,x)					\
	i = old_i;					\
}

#define BY_BLOCK(x)				\
{								\
	int old_i = i;				\
	int old_j = j;				\
	int i0 = (i/3)*3;			\
	int j0 = (j/3)*3;			\
	int l;						\
								\
	i = i0+r%3;					\
	j = j0+r/3;					\
								\
	for (l=0; l<9; l++)			\
	{							\
		x;						\
		i++;					\
								\
		if (i==i0+3)			\
		{						\
			i=i0;				\
			j++;				\
								\
			if (j==j0+3)		\
				j = j0;			\
		}						\
	}							\
								\
	i = old_i;					\
	j = old_j;					\
}

#define EXCLUSIVE_BY_FIELD(x)		\
	BY_FIELD						\
	(								\
		if (k!=old_k)				\
			x						\
	)

#define EXCLUSIVE_BY_ROW(x)			\
	BY_ROW							\
	(								\
		if (j!=old_j)				\
			x						\
	)

#define EXCLUSIVE_BY_COLUMN(x)		\
	BY_COLUMN						\
	(								\
		if (i!=old_i)				\
			x						\
	)

#define EXCLUSIVE_BY_BLOCK(x)		\
	BY_BLOCK						\
	(								\
		if (i!=old_i || j!=old_j)	\
			x						\
	)

#define BY_ALL(x)	\
	BY_FIELD(x)		\
	BY_ROW(x)		\
	BY_COLUMN(x)	\
	BY_BLOCK(x)

#define EXCLUSIVE_BY_ALL(x)		\
	EXCLUSIVE_BY_FIELD(x)		\
	EXCLUSIVE_BY_ROW(x)			\
	EXCLUSIVE_BY_COLUMN(x)		\
	EXCLUSIVE_BY_BLOCK(x)

#define DO_WITH_FIRST(by_what,x)				\
	by_what										\
	(											\
		if (possible_value[i][j][k])			\
		{										\
			x;									\
		}										\
	)

#define BLOCK_INDEX(i,j) (((i)/3)*3+(j)/3)


unsigned long int r;

void Sudoku::clean()
{
	int i,j,k;

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
		{
			possibilities_in_field[i][j] = 9;
			possibilities_in_row[i][j] = 9;
			possibilities_in_column[i][j] = 9;
			possibilities_in_block[i][j] = 9;
			known_value[i][j] = NO_VALUE;

			for (k=0; k<9; k++)
			{
				possible_value[i][j][k] = true;
			}
		}

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
			if (given_value[i][j]!=NO_VALUE)
				set(i,j,given_value[i][j]);
}

Sudoku::Sudoku()
{
    int i,j;

    for (i=0; i<9; i++)
		for (j=0; j<9; j++)
			given_value[i][j] = NO_VALUE;

	clean();
	r = 0;
}

Sudoku::Sudoku(const Sudoku &s)
{
	*this = s;
}

Sudoku & Sudoku::operator=(const Sudoku &s)
{
	int i,j,k;

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
		{
			possibilities_in_field[i][j] = s.possibilities_in_field[i][j];
			possibilities_in_row[i][j] = s.possibilities_in_row[i][j];
			possibilities_in_column[i][j] = s.possibilities_in_column[i][j];
			possibilities_in_block[i][j] = s.possibilities_in_block[i][j];
			known_value[i][j] = s.known_value[i][j];
			given_value[i][j] = s.given_value[i][j];

			for (k=0; k<9; k++)
				possible_value[i][j][k] = s.possible_value[i][j][k];
		}

	return *this;
}

bool Sudoku::operator==(const Sudoku &s) const
{
	int i,j;

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
			if (given_value[i][j]!=s.given_value[i][j])
				return false;

	return true;
}

bool Sudoku::operator!=(const Sudoku &s) const
{
	return !operator==(s);
}



void Sudoku::set(int i, int j, int k)
{
	if (known_value[i][j]==k)
		return;

	if (!possible_value[i][j][k])
		throw("The value can not be setted");

	known_value[i][j] = k;
	EXCLUSIVE_BY_ALL(reset(i,j,k))
}

void Sudoku::reset(int i, int j, int k)
{

	if (!possible_value[i][j][k])
		return;

	if (--possibilities_in_field[i][j]==0  ||
	    --possibilities_in_row[i][k]==0    ||
	    --possibilities_in_column[j][k]==0 ||
	    --possibilities_in_block[BLOCK_INDEX(i,j)][k]==0)
		throw("The value can not be reseted");

	possible_value[i][j][k] = false;

	if (possibilities_in_field[i][j]==1)
		DO_WITH_FIRST(BY_FIELD,set(i,j,k))

	if (possibilities_in_row[i][k]==1)
		DO_WITH_FIRST(BY_ROW,set(i,j,k))

	if (possibilities_in_column[j][k]==1)
		DO_WITH_FIRST(BY_COLUMN,set(i,j,k))

	if (possibilities_in_block[BLOCK_INDEX(i,j)][k]==1)
		DO_WITH_FIRST(BY_BLOCK,set(i,j,k))
}

void Sudoku::give(int i, int j, int k)
{
	try
	{
		if (known_value[i][j]==NO_VALUE)
		{
			set(i,j,k);
			find_all_possibilities();
		}

		given_value[i][j] = k;
	}
	catch(const char *message)
	{
		throw("The value can not be setted");
	}
}

void Sudoku::remove(int i, int j)
{
	given_value[i][j] = NO_VALUE;
	clean();
	find_all_possibilities();
}

enum place_type {field,row,column,block,nothing};

void Sudoku::solve()
{
	place_type pl = nothing;
	int i,j,best_first,best_second,k,min = 10;

#define FIND(possibilities,pl_type)										\
{																		\
	int i1, j1;															\
																		\
	for (i1=0; i1<9; i1++)												\
		for (j1=0; j1<9; j1++)											\
			if (possibilities[i1][j1]>1 && possibilities[i1][j1]<min)	\
			{															\
				min = possibilities[i1][j1];							\
				best_first = i1;										\
				best_second = j1;										\
				pl = pl_type;											\
																		\
				if (min==2)												\
					throw("Minimal branching has two branches");		\
			}															\
}

	try
	{
		FIND(possibilities_in_field,field)
		FIND(possibilities_in_row,row)
		FIND(possibilities_in_column,column)
		FIND(possibilities_in_block,block)
	}
	catch(const char *message)
	{
	}

#define FORK(by_what,first,second)		\
{										\
	first = best_first;					\
	second = best_second;				\
	r = rand()%9;						\
										\
	by_what								\
	(									\
		if (possible_value[i][j][k])	\
			try							\
			{							\
				Sudoku sol(*this);		\
										\
				sol.set(i,j,k);			\
				sol.solve();			\
				*this = sol;			\
										\
				return;					\
			}							\
			catch(const char *message)	\
			{							\
			}							\
	)									\
										\
	throw("Unsolvable configuration");	\
}

	if (min==10)
		return;

	i = j = k = 0;

	switch(pl)
	{
		case field:
			FORK(BY_FIELD,i,j)
			break;

		case row:
			FORK(BY_ROW,i,k)
			break;

		case column:
			FORK(BY_COLUMN,j,k)
			break;

		case block:
			i = (best_first/3)*3;
			j = (best_first%3)*3;
			k = best_second;
			int x;
			FORK(BY_BLOCK,x,x)
	}
}

void Sudoku::find_all_possibilities()
{
	int i,j,k;
	bool table[9][9][9];

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
			for (k=0; k<9; k++)
				table[i][j][k] = false;

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
			for (k=0; k<9; k++)
			{
				if (table[i][j][k])
					continue;

				if (!possible_value[i][j][k])
					continue;

				try
				{
					Sudoku sud(*this);
					int i1,j1,k1;

					sud.set(i,j,k);
					sud.solve();

					for (i1=0; i1<9; i1++)
						for (j1=0; j1<9; j1++)
							for (k1=0; k1<9; k1++)
								if (sud.possible_value[i1][j1][k1])
									table[i1][j1][k1] = true;
				}
				catch(const char *message)
				{
					reset(i,j,k);
				}
			}
}

int Sudoku::given(int i, int j) const
{
	return given_value[i][j];
}

int Sudoku::known(int i, int j) const
{
	return known_value[i][j];
}

bool Sudoku::possible(int i, int j, int k) const
{
	return possible_value[i][j][k];
}

void Sudoku::read(istream &istr)
{
	int i,j;

	for (i=0; i<9; i++)
		for (j=0; j<9; j++)
		{
			char c;

			do
			{
				istr >> c;

				if (istr.eof())
				{
					int *x = 0;
					*x = 5;

					throw("Unexpected end of file");
				}
			}
			while ((c<'1' || c>'9') && c!='.');

			if (c=='.')
				given_value[i][j] = NO_VALUE;
			else
				given_value[i][j] = c-'1';
		}

	clean();
}

void Sudoku::write(ostream &ostr) const
{
	int i,j;

	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
			if (known_value[i][j]==NO_VALUE)
				ostr << ".";
			else
				ostr << (char)(known_value[i][j]+'1');

		ostr << "\n";
	}
}

istream & operator>>(istream &istr, Sudoku &s)
{
	s.read(istr);

	return istr;
}

ostream & operator<<(ostream &ostr, const Sudoku &s)
{
	s.write(ostr);

	return ostr;
}
