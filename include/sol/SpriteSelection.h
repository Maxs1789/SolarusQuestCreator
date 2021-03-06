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
#ifndef SPRITE_SELECTION_H
#define SPRITE_SELECTION_H

#include <QString>
#include "types.h"

class SpriteSelection
{
public:
    SpriteSelection ();
    SpriteSelection (const QString &animation);
    SpriteSelection (const QString &animation, const Rect &newDirection);
    SpriteSelection (const QString &animation, const int &direction);

    bool isEmpty () const;
    bool isNewDirection () const;
    bool haveDirection () const;

    QString animation () const;
    Rect newDirection () const;
    int direction () const;

private:
    bool _isEmpty;
    QString _animation;
    Rect _newDirection;
    int _direction;
};

#endif
