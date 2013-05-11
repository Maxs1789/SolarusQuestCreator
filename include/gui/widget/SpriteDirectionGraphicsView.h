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
#ifndef SPRITE_DIRECTION_GRAPHICS_VIEW_H
#define SPRITE_DIRECTION_GRAPHICS_VIEW_H

#include "SQCGraphicsView.h"

class SpriteDirectionGraphicsView : public SQCGraphicsView
{
    Q_OBJECT
public:
    SpriteDirectionGraphicsView ();

    bool showOrigin () const;
    bool point () const;
    bool cross () const;

    void setOrigin (int originX, int originY);

public slots:
    void showOrigin (bool show);
    void showOriginPoint (bool point);
    void showOriginCross (bool cross);

signals:
    void showOriginChange (bool show, bool cross);

protected:
    void paintEvent (QPaintEvent *event);

private:
    bool _showOrigin;
    bool _cross;
    int _originX, _originY;
};

#endif
