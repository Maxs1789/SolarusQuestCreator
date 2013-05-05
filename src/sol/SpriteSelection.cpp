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
#include "sol/SpriteSelection.h"

SpriteSelection::SpriteSelection () :
    _isEmpty(true),
    _newDirection((Rect){-1, -1, -1, -1}),
    _direction(-1)
{}

SpriteSelection::SpriteSelection (const QString &animation) :
    _isEmpty(false),
    _animation(animation),
    _newDirection((Rect){-1, -1, -1, -1}),
    _direction(-1)
{}

SpriteSelection::SpriteSelection (
    const QString &animation, const Rect &newDirection
) :
    _isEmpty(false),
    _animation(animation),
    _newDirection(newDirection),
    _direction(-1)
{
    if (
        newDirection.x < 0 || newDirection.y < 0 ||
        newDirection.width <= 0 || newDirection.height <= 0
    ) {
        _newDirection = (Rect){-1, -1, -1, -1};
    }
}

SpriteSelection::SpriteSelection (
    const QString &animation, const int &direction
) :
    _isEmpty(false),
    _animation(animation),
    _newDirection((Rect){-1, -1, -1, -1}),
    _direction(direction)
{}

bool SpriteSelection::isEmpty () const
{
    return _isEmpty;
}

bool SpriteSelection::isNewDirection () const
{
    return _newDirection.x >= 0;
}

bool SpriteSelection::haveDirection () const
{
    return _direction >= 0;
}

QString SpriteSelection::animation () const
{
    if (_isEmpty) {
        return "";
    }
    return _animation;
}

Rect SpriteSelection::newDirection () const
{
    return _newDirection;
}

int SpriteSelection::direction () const
{
    return _direction;
}
