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
#include "gui/widget/TilesetComboBox.h"
#include "sol/Quest.h"

TilesetComboBox::TilesetComboBox (Quest *quest) :
    _quest(quest)
{
    quest->attach(this);
    QList<QString> ids = quest->resourceIds(TILESET);
    for (int i = 0; i < ids.size(); i++) {
        addResource(TILESET, ids[i]);
    }
}

TilesetComboBox::~TilesetComboBox ()
{
    _quest->detach(this);
}

void TilesetComboBox::refreshResource (ResourceType type, QString id)
{
    if (type == TILESET) {
        setItemText(findData(id), _quest->resourceName(TILESET, id));
    }
}

void TilesetComboBox::addResource (ResourceType type, QString id)
{
    if (type == TILESET) {
        addItem(_quest->resourceName(TILESET, id), id);
    }
}

void TilesetComboBox::removeResource (ResourceType type, QString id)
{
    if (type == TILESET) {
        removeItem(findData(id));
    }
}
