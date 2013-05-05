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
#ifndef TILE_PATTERN_EDITOR_H
#define TILE_PATTERN_EDITOR_H

#include <QWidget>
#include "sol/TilePattern.h"

class QLabel;
class QComboBox;
class QCheckBox;

class TilePatternEditor : public QWidget
{
    Q_OBJECT
public:
    TilePatternEditor (const TilePattern &tile);

    TilePattern tile () const;

    void setTile (const TilePattern &tile);

signals:
    void tileChange (TilePattern tile);

private:
    TilePattern _tile;
    QLabel *_id;
    QLabel *_position;
    QLabel *_dimension;
    QComboBox *_ground;
    QComboBox *_layer;
    QComboBox *_scrolling;
    QCheckBox *_animated;
    QComboBox *_direction;
    QComboBox *_sequence;

    void _initWidgets ();
    void _refreshWidgets (const TilePattern &tile);
    void _blockSignals (bool block);

private slots:
    void _groundChange ();
    void _layerChange ();
    void _scrollingChange ();
    void _animationChange ();
};

#endif
