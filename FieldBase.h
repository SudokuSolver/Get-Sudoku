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


#ifndef FIELDBASE_H
#define FIELDBASE_H

#include <QtGui/QFrame>
#include <QtGui/QResizeEvent>
#include "Digit.h"


enum FieldType {given, calculated, unknown};

class FieldBase : public QFrame
{
protected:

    int row, column, data;
    int size;

public:

    FieldBase(int, int, QWidget* = 0);

    virtual FieldType fieldType() const = 0;
    virtual void setData(int);

protected:

    void resizeEvent(QResizeEvent*);
    virtual void whenResized(int = -1);
};

#endif // FIELDBASE_H
