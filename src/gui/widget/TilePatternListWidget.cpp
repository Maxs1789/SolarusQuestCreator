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
#include <QHeaderView>
#include "gui/widget/TilePatternListWidget.h"
#include "sol/Tileset.h"
#include "sol/TilePattern.h"

TilePatternListWidget::TilePatternListWidget () :
    _tileset(0)
{}

TilePatternListWidget::~TilePatternListWidget ()
{
    if (_tileset != 0) {
        _tileset->detach(this);
    }
}

void TilePatternListWidget::setTileset (Tileset *tileset)
{
    if (_tileset != 0) {
        _tileset->detach(this);
    }
    _tileset = tileset;
    if (_tileset != 0) {
        _tileset->attach(this);
        _refresh();
        setEnabled(true);
    } else if (isEnabled()) {
        setEnabled(false);
    }
}

void TilePatternListWidget::refreshSelection (QList<int> selection)
{

}

void TilePatternListWidget::refreshPattern (int id)
{

}

void TilePatternListWidget::addPatterns (QList<int> selection)
{
    QList<TilePattern> list = _tileset->patterns(selection);
    int len = list.size();
    for (int i = 0; i < len; i++) {
        _addPattern(list[i]);
    }
}

void TilePatternListWidget::removePatterns (QList<int> selection)
{

}

void TilePatternListWidget::_refresh ()
{
    clear();
    QList<TilePattern> patterns = _tileset->allPatterns();
    int len = patterns.size();
    for (int i = 0; i < len; i++) {
        _addPattern(patterns[i]);
    }
}

void TilePatternListWidget::_addPattern (const TilePattern &pattern)
{
    addItem(QString::number(pattern.id()));
}
