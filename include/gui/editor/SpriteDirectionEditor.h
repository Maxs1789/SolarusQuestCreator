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
#ifndef SPRITE_DIRECTION_EDITOR_H
#define SPRITE_DIRECTION_EDITOR_H

#include <QWidget>
#include "sol/SpriteDirection.h"

class QSpinBox;

class SpriteDirectionEditor : public QWidget
{
    Q_OBJECT
public:
    SpriteDirectionEditor ();

    SpriteDirection direction () const;

    void setDirection (const SpriteDirection &direction);

signals:
    void directionChange (SpriteDirection direction);
    void directDirectionChange (SpriteDirection direction);

private:
    SpriteDirection _direction;
    QSpinBox *_x;
    QSpinBox *_y;
    QSpinBox *_width;
    QSpinBox *_height;
    QSpinBox *_originX;
    QSpinBox *_originY;
    QSpinBox *_nbFrames;
    QSpinBox *_nbColumns;

    void _initWidgets ();
    void _refreshWidgets (const SpriteDirection &direction);
    void _blockSignals (bool block);

private slots:
    void _xChange ();
    void _yChange ();
    void _widthChange ();
    void _heightChange ();
    void _originXChange ();
    void _originYChange ();
    void _nbFramesChange ();
    void _nbColumnsChange ();

    void _directXChange ();
    void _directYChange ();
    void _directWidthChange ();
    void _directHeightChange ();
    void _directOriginXChange ();
    void _directOriginYChange ();
    void _directNbFramesChange ();
    void _directNbColumnsChange ();
};

#endif
