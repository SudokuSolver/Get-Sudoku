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


#include <QtGui/QResizeEvent>
#include "MainWindow.h"
#include "Sudoku.h"


#define DISTANCE_FROM_WINDOW	20
#define FRAME_THICKNESS			10
#define DISTANCE_FROM_FRAME		10
#define FIELD_SIZE				100
#define SPACE					8
#define DISTANCE_FROM_LINE		6
#define LINE_THICKNESS			6
#define TOTAL					(							\
	2*DISTANCE_FROM_WINDOW		+							\
	2*FRAME_THICKNESS			+							\
	2*DISTANCE_FROM_FRAME		+							\
	9*FIELD_SIZE				+							\
	6*SPACE						+							\
	4*LINE_THICKNESS			+							\
	2*LINE_THICKNESS			)

#define CORRECTION(x) ((2*(x)*maxSize+TOTAL)/(2*TOTAL))

MainWindow::MainWindow(QWidget *w, int size) : QMainWindow(w)
{
    width = height = (size>0 ? size : 600);
    resize(width, height);
    setupUi(this);
    leftEdge = new Bar(supporter);
	rightEdge = new Bar(supporter);
	topEdge = new Bar(supporter);
	bottomEdge = new Bar(supporter);
	firstHorizontalLine = new Bar(supporter);
	secondHorizontalLine = new Bar(supporter);
	firstVerticalLine = new Bar(supporter);
	secondVerticalLine = new Bar(supporter);

    int i, j;

    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            field[i][j] = new Field(i, j, supporter);

    whenResize();
    show();
}

MainWindow::~MainWindow()
{
    int i, j;

    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            delete field[i][j];
}

void MainWindow::whenResize(int oldWidth, int oldHeight)
{
    int maxSize = (width<height ? width : height);

    frameThickness = CORRECTION(FRAME_THICKNESS);
	distanceFromFrame = CORRECTION(DISTANCE_FROM_FRAME);
	fieldSize = CORRECTION(FIELD_SIZE);
	space = CORRECTION(SPACE);
	distanceFromLine = CORRECTION(DISTANCE_FROM_LINE);
	lineThickness = CORRECTION(LINE_THICKNESS);
	totalSize =
		2*frameThickness +
		2*distanceFromFrame +
		9*fieldSize +
		6*space +
		4*distanceFromLine +
		2*lineThickness;
	distanceFromWindow = ((maxSize-totalSize)/2);
	supporter->setGeometry((width-totalSize)/2, (height-totalSize)/2, totalSize, totalSize);
    leftEdge->setGeometry(0,0,frameThickness,totalSize);
    rightEdge->setGeometry(totalSize-frameThickness,0,frameThickness,totalSize);
    topEdge->setGeometry(0,0,totalSize,frameThickness);
    bottomEdge->setGeometry(0,totalSize-frameThickness,totalSize,frameThickness);
    firstHorizontalLine->setGeometry(0,
        frameThickness+distanceFromFrame+3*fieldSize+2*space+distanceFromLine,
        totalSize,
        lineThickness);
    secondHorizontalLine->setGeometry(0,
        frameThickness+distanceFromFrame+6*fieldSize+4*space+3*distanceFromLine+lineThickness,
        totalSize,
        lineThickness);
    firstVerticalLine->setGeometry(frameThickness+distanceFromFrame+3*fieldSize+2*space+distanceFromLine,
        0,
        lineThickness,
        totalSize);
    secondVerticalLine->setGeometry(frameThickness+distanceFromFrame+6*fieldSize+4*space+3*distanceFromLine+lineThickness,
        0,
        lineThickness,
        totalSize);

    int lowerBound[9], upperBound[9];
    int i, j;

    for (i=0; i<9; i++)
    {
        lowerBound[i] =
            frameThickness+distanceFromFrame+i*(fieldSize+space)+(i/3)*(2*distanceFromLine+lineThickness-space);
        upperBound[i] = lowerBound[i] + fieldSize;
    }

    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            field[i][j]->setGeometry(lowerBound[i], lowerBound[j], fieldSize, fieldSize);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    width = event->size().width();
    height = event->size().height();
    whenResize();
    QWidget::resizeEvent(event);
}

void MainWindow::updateData()
{
    int i, j;

    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            field[i][j]->update();
}

MainWindow *mainWindow;
