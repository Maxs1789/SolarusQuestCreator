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
#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <QString>
#include <QList>
#include "SpriteDirection.h"

class SpriteAnimation
{
public:
    SpriteAnimation (
        QString name = "", QString image = "",
        int frameDelay = 0, int frameOnLoop = -1
    );
    SpriteAnimation (const SpriteAnimation &other, QString name);

    QString name () const;
    QString image () const;
    int frameDelay () const;
    int frameOnLoop () const;

    int countDirections () const;
    SpriteDirection direction (const int &n) const throw(SQCException);
    QList<SpriteDirection> allDirections () const;

    int maxNbFrames () const;

    void setImage (const QString &image);
    void setFrameDelay (const int &frameDelay) throw(SQCException);
    void setFrameOnLoop (const int &frameOnLoop) throw(SQCException);

    int addDirection (const SpriteDirection &direction);
    void setDirection (const int &n, const SpriteDirection &direction);
    void removeDirection (const int &n) throw(SQCException);

    void swapDirection (const int &n1, const int &n2) throw(SQCException);

    QString toData () const;

private:
    QString _name;
    QString _image;
    int _frameDelay;
    int _frameOnLoop;
    QList<SpriteDirection> _directions;

    void _checkDirectionExists (int n) const throw(SQCException);
    void _checkFrameDelay (int frameDelay) const throw(SQCException);
    void _checkFrameOnLoop (int frameOnLoop) const throw(SQCException);
};

#endif
