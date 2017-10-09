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


#include "KnownField.h"


KnownField::KnownField(int row, int column, int value, QWidget *parent)
    :   FieldBase(row, column, parent)
{
    label = new Digit(row, column, value, this);
    whenResized();
}

#define HORIZONTAL_DISTANCE 10
#define VERTICAL_DISTANCE   10
#define TOTAL_SIZE          100

void KnownField::whenResized(int oldSize)
{
    if (size==oldSize)
        return;

    QFont font;
    int left, top, width, height, size;

    size = this->size-4;
    left = (size*HORIZONTAL_DISTANCE)/(2*TOTAL_SIZE);
    top = (size*VERTICAL_DISTANCE)/(2*TOTAL_SIZE);
    width = size-2*left;
    height = size-2*top;
    left += 2;
    top += 2;
    font = label->font();
    font.setPixelSize(height/3);
    setFont(font);
    label->setGeometry(left,top,width,height);
}

void KnownField::setData(int x)
{
    value = data;
}
