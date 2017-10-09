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


#include "Field.h"
#include "Sudoku.h"
#include "MainWindow.h"


Field::Field(int row, int column, QWidget *parent)
{
    this->row = row;
    this->column = column;
    this->parent = parent;
    data = 0x1ff;
    field = new UnknownField(row, column, data, parent);
    this->left = field->geometry().left();
    this->top = field->geometry().top();
    this->width = field->geometry().width();
    this->height = field->geometry().height();
}

Field::~Field()
{
    field->close();
}

void Field::setGeometry(int left, int top, int width, int height)
{
    if (this->left==left && this->top==top && this->width==width && this->height==height)
        return;

    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
    field->setGeometry(left, top, width, height);
}

void Field::update()
{
    if (solver.given(row, column)!=NO_VALUE)
    {
        if (field->fieldType()==given)
            return;

        field->close();
        field = new GivenField(row, column, solver.given(row, column), parent);
        field->setGeometry(left, top, width, height);
        field->show();

        return;
    }

    if (solver.known(row, column)!=NO_VALUE)
    {
        if (field->fieldType()==calculated)
            return;

        field->close();
        field = new CalculatedField(row, column, solver.known(row, column), parent);
        field->setGeometry(left, top, width, height);
        field->show();

        return;
    }

    int i;

    data = 0;

    for (i=0; i<9; i++)
        if (solver.possible(row, column, i))
            data |= 1<<i;

    if (field->fieldType()!=unknown)
    {
        field->close();
        field = new UnknownField(row, column, data, parent);
        field->setGeometry(left, top, width, height);
        field->show();

        return;
    }

    field->setData(data);
}
