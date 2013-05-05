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
#ifndef SQC_TREE_WIDGET_H
#define SQC_TREE_WIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>

class SQCTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    SQCTreeWidget () {}

    void contextMenuEvent (QContextMenuEvent *event)
    {
        QTreeWidgetItem *item = itemAt(event->pos());
        if (item != 0) {
            emit itemContextMenu(item, event->globalPos());
        }
    }

signals:
    void itemContextMenu (QTreeWidgetItem *, QPoint);
};

#endif
