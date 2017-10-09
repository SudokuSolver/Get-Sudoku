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


#include <QtGui/QBrush>
#include "Label.h"


Label::Label(QChar value, QWidget *parent) : QLabel(parent)
{
    width = QLabel::width();
    height = QLabel::height();
    this-> value = value;
    setText(value);
    setAutoFillBackground(true);
    setPalette(palette);
    setBackgroundRole(QPalette::Background);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void Label::setBkColor(QColor color)
{
    palette.setBrush(QPalette::Background, QBrush(color));
    setPalette(palette);
}

void Label::setTextColor(QColor color)
{
    palette.setColor(QPalette::WindowText, color);
    setPalette(palette);
}

QColor Label::getBkColor() const
{
    return palette.brush(QPalette::Background).color();

}

QColor Label::getTextColor() const
{
    return palette.color(QPalette::WindowText);
}

void Label::whenClicked()
{
    QColor bk,tx;
    bk = getBkColor();
    tx = getTextColor();
    setBkColor(tx);
    setTextColor(bk);
}

void Label::whenResized(int oldWidth, int oldHeight)
{
    QFont font;

    font = QWidget::font();
    font.setPixelSize(height);
    setFont(font);
}

void Label::mousePressEvent(QMouseEvent *event)
{
    whenClicked();
    QWidget::mousePressEvent(event);
}

void Label::resizeEvent(QResizeEvent *event)
{
    int oldWidth, oldHeight;

    oldWidth = event->oldSize().width();
    oldHeight = event->oldSize().height();
    width = event->size().width();
    height = event->size().height();
    whenResized(oldWidth, oldHeight);
    QWidget::resizeEvent(event);
}
