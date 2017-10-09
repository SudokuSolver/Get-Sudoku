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


#include "UnknownField.h"


#define DISTANCE_FROM_VERTICAL_EDGE			10
#define DISTANCE_FROM_HORIZONTAL_EDGE		10
#define WIDTH								75
#define HEIGHT								100
#define HORIZONTAL_SPACE					30
#define VERTICAL_SPACE						20
#define TOTAL_HORIZONTAL				(	\
	2*DISTANCE_FROM_VERTICAL_EDGE		+	\
	3*WIDTH								+	\
	2*HORIZONTAL_SPACE						)
#define TOTAL_VERTICAL					(	\
	2*DISTANCE_FROM_HORIZONTAL_EDGE		+	\
	3*HEIGHT							+	\
	2*VERTICAL_SPACE					)
#define TOTAL_HORIZONTAL_SIZE			(	\
	3*WIDTH								+	\
	2*HORIZONTAL_SPACE					)
#define TOTAL_VERTICAL_SIZE				(	\
	3*HEIGHT							+	\
	2*VERTICAL_SPACE					)
#define HORIZONTAL_CORRECTION(x) ((2*(x)*fieldSize+TOTAL_HORIZONTAL)/(2*TOTAL_HORIZONTAL))
#define VERTICAL_CORRECTION(x) ((2*(x)*fieldSize+TOTAL_VERTICAL)/(2*TOTAL_VERTICAL))
#define FIELD_SIZE_CORRECTION(x) ((x)-2)


UnknownField::UnknownField(int row, int column, int data, QWidget *parent)
    :   FieldBase(row, column, parent)
{
    int i;

    for (i=0; i<9; i++)
        digit[i] = new Digit(row, column, i, this);

    setData(data);
    setLineWidth(1);
    setFrameShadow(QFrame::Plain);
    whenResized();
}

void UnknownField::setData(int x)
{
    int i;

    data = x;

    for (i=0; i<9; i++)
	{
		if ((data&(1<<i))==0)
			digit[i]->hide();
		else
			digit[i]->show();
	}
}

void UnknownField::whenResized(int oldSize)
{
    if (size==oldSize)
        return;

	int width;
	int height;
	int horizontalSpace;
	int verticalSpace;
	int totalHorizontalSize;
	int totalVerticalSize;
	int distanceFromHorizontalEdge;
	int distanceFromVerticalEdge;
	int fieldSize;

	fieldSize = FIELD_SIZE_CORRECTION(size);
    width = HORIZONTAL_CORRECTION(WIDTH);
	height = VERTICAL_CORRECTION(HEIGHT);
	horizontalSpace = HORIZONTAL_CORRECTION(HORIZONTAL_SPACE);
	verticalSpace = VERTICAL_CORRECTION(VERTICAL_SPACE);
	totalHorizontalSize = 3*width+2*horizontalSpace;
	totalVerticalSize = 3*height+2*verticalSpace;
	distanceFromVerticalEdge = (size-totalHorizontalSize)/2;
	distanceFromHorizontalEdge = (size-totalVerticalSize)/2;

	int horizontalLowerBound[9], horizontalUpperBound[9],
	    verticalLowerBound[9], verticalUpperBound[9];
    int i;

    for (i=0; i<9; i++)
	{
	    QFont font;

	    font = this->font();
	    font.setPixelSize(height);
	    setFont(font);
		horizontalLowerBound[i] = distanceFromVerticalEdge+(i%3)*(width+horizontalSpace);
		horizontalUpperBound[i] = horizontalLowerBound[i]+width;
		verticalLowerBound[i] = distanceFromHorizontalEdge+(i/3)*(height+verticalSpace);
		verticalUpperBound[i] = verticalLowerBound[i]+height;
		digit[i]->setGeometry(horizontalLowerBound[i], verticalLowerBound[i], width, height);
	}
}

FieldType UnknownField::fieldType() const
{
    return unknown;
}
