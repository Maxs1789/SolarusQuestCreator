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
#ifndef SPRITE_DIRECTION_H
#define SPRITE_DIRECTION_H

#include "exception/SQCException.h"

class SpriteDirection
{
public:
    SpriteDirection (
        int x = 0, int y = 0, int width = 24, int height = 24,
        int originX = 12, int originY = 12, int nbFrames = 1, int nbColumns = 1
    ) throw (SQCException);

    bool operator!= (const SpriteDirection &other);

    int x () const;
    int y () const;
    int width () const;
    int height () const;
    int originX () const;
    int originY() const;
    int nbFrames() const;
    int nbColumns () const;

    void setX (const int &x) throw (SQCException);
    void setY (const int &y) throw (SQCException);
    void setWidth (const int &width) throw (SQCException);
    void setHeight (const int &height) throw (SQCException);
    void setOriginX (const int &originX);
    void setOriginY (const int &originY);
    void setNbFrames (const int &nbFrames) throw (SQCException);
    void setNbColumns (const int &nbColumns) throw (SQCException);

private:
    int _x, _y, _width, _height, _originX, _originY, _nbFrames, _nbColumns;

    void _checkX (const int &x) const throw (SQCException);
    void _checkY (const int &y) const throw (SQCException);
    void _checkWidth (const int &width) const throw (SQCException);
    void _checkHeight (const int &height) const throw (SQCException);
    void _checkNbFrames (const int &nbFrames) const throw (SQCException);
    void _checkNbColumns (const int &nbColumns) const throw (SQCException);
};

#endif
