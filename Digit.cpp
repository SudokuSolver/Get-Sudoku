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


#include "Digit.h"
#include "Sudoku.h"
#include "MainWindow.h"


Digit::Digit(int row, int column, int value, QWidget *parent) : Label(QChar('1'+value), parent)
{
    this->row = row;
    this->column = column;
    this->value = value;
}

void Digit::whenClicked()
{
    if (solver.given(row,column)!=NO_VALUE)
        solver.remove(row, column);
    else
        solver.give(row, column, value);

    mainWindow->updateData();
}
