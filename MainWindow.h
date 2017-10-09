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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Bar.h"
#include "Field.h"


class MainWindow : public QMainWindow, public Ui_MainWindow
{
    int width, height,
    frameThickness,
    distanceFromFrame,
	fieldSize,
	space,
	distanceFromLine,
	lineThickness,
	totalSize,
	distanceFromWindow;

    Bar *leftEdge, *rightEdge, *topEdge, *bottomEdge,
		*firstHorizontalLine, *secondHorizontalLine,
		*firstVerticalLine, *secondVerticalLine;

    Field *field[9][9];

protected:

    void resizeEvent(QResizeEvent *);
    void whenResize(int = -1, int = -1);

public:

    MainWindow(QWidget* = 0, int = 0);
    ~MainWindow();

    void updateData();
};

extern MainWindow *mainWindow;

#endif // MAINWINDOW_H
