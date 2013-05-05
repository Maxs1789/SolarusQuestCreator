/*
 * Solarus Quest Creator - GUI to build games for Solarus engine
 * Copyright (C) 2013, Van den Branden Maxime <max.van.den.branden@gmail.com>
 *
 * Licensed under the EUPL, Version 1.1
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the Licence is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the Licence for the specific language governing permissions and
 * limitations under the Licence.
 */
#include <QObject>
#include "sol/SpriteDirection.h"

SpriteDirection::SpriteDirection (
    int x, int y, int width, int height,
    int originX, int originY, int nbFrames, int nbColumns
) throw (SQCException) :
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _originX(originX),
    _originY(originY),
    _nbFrames(nbFrames),
    _nbColumns(nbColumns)
{
    _checkX(x);
    _checkY(y);
    _checkWidth(width);
    _checkHeight(height);
    _checkNbFrames(nbFrames);
    _checkNbColumns(nbColumns);
}

bool SpriteDirection::operator!= (const SpriteDirection &other)
{
    return other._x        != _x        || other._y         != _y
        || other._width    != _width    || other._height    != _height
        || other._originX  != _originX  || other._originY   != _originY
        || other._nbFrames != _nbFrames || other._nbColumns != _nbColumns;
}

int SpriteDirection::x () const
{
    return _x;
}

int SpriteDirection::y () const
{
    return _y;
}

int SpriteDirection::width () const
{
    return _width;
}

int SpriteDirection::height () const
{
    return _height;
}

int SpriteDirection::originX () const
{
    return _originX;
}

int SpriteDirection::originY() const
{
    return _originY;
}

int SpriteDirection::nbFrames() const
{
    return _nbFrames;
}

int SpriteDirection::nbColumns () const
{
    return _nbColumns;
}

void SpriteDirection::setX (const int &x) throw (SQCException)
{
    _checkX(x);
    _x = x;
}

void SpriteDirection::setY (const int &y) throw (SQCException)
{
    _checkY(y);
    _y = y;
}

void SpriteDirection::setWidth (const int &width) throw (SQCException)
{
    _checkWidth(width);
    _width = width;
}

void SpriteDirection::setHeight (const int &height) throw (SQCException)
{
    _checkHeight(height);
    _height = height;
}

void SpriteDirection::setOriginX (const int &originX)
{
    _originX = originX;
}

void SpriteDirection::setOriginY (const int &originY)
{
    _originY = originY;
}

void SpriteDirection::setNbFrames (const int &nbFrames) throw (SQCException)
{
    _checkNbFrames(nbFrames);
    _nbFrames = nbFrames;
}

void SpriteDirection::setNbColumns (const int &nbColumns) throw (SQCException)
{
    _checkNbColumns(nbColumns);
    _nbColumns = nbColumns;
}

void SpriteDirection::_checkX (const int &x) const throw (SQCException)
{
    if (x < 0) {
        throw SQCException(QObject::tr("x must greater or equals than 0"));
    }
}

void SpriteDirection::_checkY (const int &y) const throw (SQCException)
{
    if (y < 0) {
        throw SQCException(QObject::tr("y must greater or equals than 0"));
    }
}

void SpriteDirection::_checkWidth (const int &width) const throw (SQCException)
{
    if (width <= 0) {
        throw SQCException(QObject::tr("width must be greater than 0"));
    }
}

void SpriteDirection::_checkHeight (const int &height) const
    throw (SQCException)
{
    if (height <= 0) {
        throw SQCException(QObject::tr("height must be greater than 0"));
    }
}

void SpriteDirection::_checkNbFrames (const int &nbFrames) const
    throw (SQCException)
{
    if (nbFrames < 1) {
        throw SQCException(
            QObject::tr("number of frames must be greater than 0")
        );
    }
}

void SpriteDirection::_checkNbColumns (const int &nbColumns) const
    throw (SQCException)
{
    if (nbColumns < 1) {
        throw SQCException(
            QObject::tr("number of columns must be greater than 0")
        );
    }
}
