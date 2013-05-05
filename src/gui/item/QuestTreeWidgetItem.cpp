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
#include <QCommonStyle>
#include "gui/item/QuestTreeWidgetItem.h"
#include "sol/Quest.h"

QuestTreeWidgetItem::QuestTreeWidgetItem (Quest *quest) :
    _quest(quest)
{
    _initWidgets();
    setText(0, quest->titleBar());
    _quest->attach(this);
    for (int i = MAP; i < N_RESOURCE_TYPE; i++) {
        ResourceType type = (ResourceType)i;
        QList<QString> ids = quest->resourceIds(type);
        for (int j = 0; j < ids.size(); ++j) {
            addResource(type, ids[j]);
        }
    }
}

void QuestTreeWidgetItem::refreshResource (ResourceType type, QString id)
{
    _resourceItems[type][id]->setText(0, _quest->resourceName(type, id));
}

void QuestTreeWidgetItem::addResource (ResourceType type, QString id)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ITEM_RESOURCE);
    item->setData(0, ROLE_QUEST, _quest->directory());
    item->setData(0, ROLE_TYPE, type);
    item->setData(0, ROLE_ID, QVariant(id));
    item->setText(0, _quest->resourceName(type, id));
    item->setIcon(0, QIcon(":fugue/file"));
    _resources[type]->addChild(item);
    _resourceItems[type][id] = item;
}

void QuestTreeWidgetItem::removeResource (ResourceType type, QString id)
{
    _resources[type]->removeChild(_resourceItems[type][id]);
    delete _resourceItems[type][id];
    _resourceItems[type].remove(id);
}

void QuestTreeWidgetItem::setBold (bool bold)
{
    QFont f = font(0);
    f.setBold(bold);
    setFont(0, f);
}

void QuestTreeWidgetItem::_initWidgets ()
{
    _resources[MAP] = new QTreeWidgetItem(0);
    _resources[TILESET] = new QTreeWidgetItem(0);
    _resources[MUSIC] = new QTreeWidgetItem(0);
    _resources[SPRITE] = new QTreeWidgetItem(0);
    _resources[SOUND] = new QTreeWidgetItem(0);
    _resources[ITEM] = new QTreeWidgetItem(0);
    _resources[ENEMY] = new QTreeWidgetItem(0);
    _resources[LANGUAGE] = new QTreeWidgetItem(0);

    _resources[MAP]->setText(0, QObject::tr("Map"));
    _resources[TILESET]->setText(0, QObject::tr("Tileset"));
    _resources[MUSIC]->setText(0, QObject::tr("Music"));
    _resources[SPRITE]->setText(0, QObject::tr("Sprite"));
    _resources[SOUND]->setText(0, QObject::tr("Sound"));
    _resources[ITEM]->setText(0, QObject::tr("Item"));
    _resources[ENEMY]->setText(0, QObject::tr("Enemy"));
    _resources[LANGUAGE]->setText(0, QObject::tr("Language"));

    QCommonStyle style;
    _resources[MAP]->setIcon(0, QIcon(":fugue/dir"));
    _resources[TILESET]->setIcon(0, QIcon(":fugue/dir"));
    _resources[MUSIC]->setIcon(0, QIcon(":fugue/dir"));
    _resources[SPRITE]->setIcon(0, QIcon(":fugue/dir"));
    _resources[SOUND]->setIcon(0, QIcon(":fugue/dir"));
    _resources[ITEM]->setIcon(0, QIcon(":fugue/dir"));
    _resources[ENEMY]->setIcon(0, QIcon(":fugue/dir"));
    _resources[LANGUAGE]->setIcon(0, QIcon(":fugue/dir"));
    setIcon(0, QIcon(":fugue/box"));

    //addChild(_resources[TILESET]);
    addChild(_resources[SPRITE]);
    /*addChild(_resources[MUSIC]);
    addChild(_resources[SOUND]);
    addChild(_resources[LANGUAGE]);
    addChild(_resources[ITEM]);
    addChild(_resources[ENEMY]);
    addChild(_resources[MAP]);*/
}
