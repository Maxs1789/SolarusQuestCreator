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
#ifndef TILE_PATTERN_TABLE_WIDGET_H
#define TILE_PATTERN_TABLE_WIDGET_H

#include <QListWidget>
#include "view/TilesetView.h"
#include "sol/types.h"

class TilePatternListWidget : public QListWidget, public TilesetView
{
    Q_OBJECT
public:
    TilePatternListWidget ();
    ~TilePatternListWidget ();

    void setTileset (Tileset *tileset);

    void simpleRefresh (QString message) {}
    void refreshSelection (QList<int> selection);
    void refreshPattern (int id);
    void addPatterns (QList<int> selection);
    void removePatterns (QList<int> selection);

private:
    Tileset *_tileset;

    void _refresh ();
    void _addPattern (const TilePattern &pattern);
};

#endif
