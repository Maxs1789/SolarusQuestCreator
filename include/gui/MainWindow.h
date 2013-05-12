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
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QModelIndex>
#include "item/QuestTreeWidgetItem.h"

class QMdiArea;
class SQCTreeWidget;
class QTreeWidgetItem;
class Editor;

/**
 * @brief Fenetre principale de l'application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la fenetre principale.
     */
    MainWindow ();
    /**
     * @brief Destructeur de la fenetre principale.
     */
    ~MainWindow ();

private:
    QMap<QString, Quest *> _quests;
    QString _currentQuest;
    QMdiArea *_mdiArea;
    SQCTreeWidget *_treeWidget;
    QMenuBar *_menuBar;
    QMenu *_fileMenu;
    //QMenu *_editMenu;
    QMenu *_resourceMenu;
    QMenu *_spriteMenu;
    QAction *_openQuestAction;
    QAction *_newSpriteAction;
    QMap<QString, QuestTreeWidgetItem *> _questItems;
    QMap<QString, QMap<QString, Editor *> > _editors[N_RESOURCE_TYPE];
    QMenu *_treeMenu;
    QAction *_editTreeAction;
    QAction *_removeTreeAction;

    void _initWidgets ();
    void _initMenus ();
    void _connects ();

private slots:
    void _openQuest ();
    void _openEditor (QTreeWidgetItem* item, int);
    void _openEditor (Quest *quest, ResourceType type, QString id);
    void _closeEditor (Editor *editor);
    void _resourceContextMenu (QTreeWidgetItem* item, QPoint pos);
    void _resourceEdit ();
    void _resourceRemove ();
    void _newSprite ();
    void _openNewResourceDialog (ResourceType type);
    void _saveResource (Editor *editor);
};

#endif
