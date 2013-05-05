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
#ifndef QUEST_TREE_WIDGET_ITEM_H
#define QUEST_TREE_WIDGET_ITEM_H

#include <QTreeWidgetItem>
#include "view/QuestView.h"

#define ITEM_RESOURCE 2

#define ROLE_QUEST QTreeWidgetItem::UserType + 1
#define ROLE_TYPE  QTreeWidgetItem::UserType + 2
#define ROLE_ID    QTreeWidgetItem::UserType + 3

class QuestTreeWidgetItem : public QTreeWidgetItem, public QuestView
{
public:
    QuestTreeWidgetItem (Quest *quest);

    void refreshResource (ResourceType type, QString id);
    void addResource (ResourceType type, QString id);
    void removeResource (ResourceType type, QString id);

    void setBold (bool bold);

private:
    Quest *_quest;
    QTreeWidgetItem *_resources[N_RESOURCE_TYPE];
    QMap<QString, QTreeWidgetItem *> _resourceItems[N_RESOURCE_TYPE];

    void _initWidgets ();
};

#endif
