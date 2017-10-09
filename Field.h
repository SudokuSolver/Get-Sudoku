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


#ifndef FIELD_H
#define FIELD_H

#include "UnknownField.h"
#include "KnownField.h"
#include "GivenField.h"
#include "CalculatedField.h"


class Field
{
    FieldBase *field;
    QWidget *parent;
    int left, top, width, height;
    int row, column, data;

public:

    Field(int, int, QWidget* = 0);
    ~Field();

    void setGeometry(int, int, int, int);
    void update();
};

#endif // FIELD_H
