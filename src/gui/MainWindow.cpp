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
#include <QMdiArea>
#include <QSplitter>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include "gui/MainWindow.h"
#include "gui/widget/SQCTreeWidget.h"
#include "gui/editor/TilesetEditor.h"
#include "gui/editor/SpriteEditor.h"
#include "sol/Quest.h"
#include "gui/item/QuestTreeWidgetItem.h"
#include "gui/dialog/NewResourceDialog.h"

#include "util/FileTools.h"

MainWindow::MainWindow ()
{
    _initWidgets();
    _initMenus();
    _connects();
}

MainWindow::~MainWindow ()
{
    QMap<QString, Quest *>::Iterator it;
    for (it = _quests.begin(); it != _quests.end(); it++) {
        for (int type = MAP; type < N_RESOURCE_TYPE; ++type) {
            QMap<QString, QMap<QString, Editor *> > m = _editors[type];
            QList<Editor *> editors = m[it.value()->directory()].values();
            for (int i = 0; i < editors.size(); i++) {
                delete editors[i];
            }
        }
        delete it.value();
    }
}

void MainWindow::_initWidgets ()
{
    _mdiArea = new QMdiArea;
    _treeWidget = new SQCTreeWidget;

    //_mdiArea->setViewMode(QMdiArea::TabbedView);
    _treeWidget->setHeaderHidden(true);

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(_treeWidget);
    splitter->addWidget(_mdiArea);
    setCentralWidget(splitter);
}

void MainWindow::_initMenus ()
{
    _menuBar = new QMenuBar(this);
    _fileMenu = new QMenu(tr("&File"));
    //_editMenu = new QMenu(tr("&Edit"));
    _resourceMenu = new QMenu(tr("&Resource"));
    _spriteMenu = new QMenu(tr("&Sprite"));

    _newSpriteAction = _spriteMenu->addAction(tr("&New Sprite"));
    _openQuestAction = _fileMenu->addAction(tr("&Open Quest"));
    _openQuestAction->setShortcut(QKeySequence(tr("Ctrl+O")));

    _resourceMenu->addMenu(_spriteMenu);
    _resourceMenu->setEnabled(false);

    _menuBar->addMenu(_fileMenu);
    //_menuBar->addMenu(_editMenu);
    _menuBar->addMenu(_resourceMenu);
    setMenuBar(_menuBar);

    _treeMenu = new QMenu(_treeWidget);
    _editTreeAction = _treeMenu->addAction(tr("Edit"));
    _removeTreeAction = _treeMenu->addAction(tr("Remove"));
}

void MainWindow::_connects ()
{
    connect(_openQuestAction, SIGNAL(triggered()), this, SLOT(_openQuest()));
    connect(
        _treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
        this, SLOT(_openEditor(QTreeWidgetItem *, int))
    );
    connect(
        _treeWidget, SIGNAL(itemContextMenu(QTreeWidgetItem*, QPoint)),
        this, SLOT(_resourceContextMenu(QTreeWidgetItem*, QPoint))
    );
    connect(_newSpriteAction, SIGNAL(triggered()), this, SLOT(_newSprite()));
    connect(_editTreeAction, SIGNAL(triggered()), this, SLOT(_resourceEdit()));
    connect(
        _removeTreeAction, SIGNAL(triggered()), this, SLOT(_resourceRemove())
    );
}

void MainWindow::_openQuest ()
{
    QString directory = QFileDialog::getExistingDirectory(this);
    if (directory == "") {
        return;
    }
    QString dir = FileTools::absolutePath(directory);
    if (_quests.contains(dir)) {
        QMessageBox::warning(
            this, tr("Warning"), tr("This Quest is already open.")
        );
        return;
    }
    try {
        Quest *quest = Quest::load(dir);
        _quests[dir] = quest;
        _questItems[dir] = new QuestTreeWidgetItem(quest);
        _treeWidget->addTopLevelItem(_questItems[dir]);
        if (_questItems.contains(_currentQuest)) {
            _questItems[_currentQuest]->setBold(false);
        }
        _currentQuest = dir;
        _questItems[dir]->setBold(true);
        _resourceMenu->setEnabled(true);
    } catch (const QuestException &ex) {
        QMessageBox::critical(this, tr("Error"), ex.what());
    }
}

void MainWindow::_openEditor (QTreeWidgetItem* item, int)
{
    if (item->type() != ITEM_RESOURCE) {
        return;
    }
    QString dir = item->data(0, ROLE_QUEST).toString();
    ResourceType type = (ResourceType)item->data(0, ROLE_TYPE).toInt();
    QString id = item->data(0, ROLE_ID).toString();
    if (_quests.contains(dir)) {
        Quest *quest = _quests[dir];
        if (quest->resourceExists(type, id)) {
            _openEditor(quest, type, id);
        }
    }
}

void MainWindow::_openEditor (Quest *quest, ResourceType type, QString id)
{
    QString dir = quest->directory();
    if (!_editors[type][dir].contains(id)) {
        if (type == SPRITE) {
            SpriteEditor *editor = new SpriteEditor(quest, quest->sprite(id));
            _editors[SPRITE][dir][id] = editor;
            _mdiArea->addSubWindow(editor);
            connect(
                editor, SIGNAL(close(Editor*)),
                this, SLOT(_closeEditor(Editor*))
            );
            connect(
                editor, SIGNAL(save(Editor*)),
                this, SLOT(_saveResource(Editor*))
            );
        }
    }
    _editors[type][dir][id]->show();
    _editors[type][dir][id]->setFocus();
}

void MainWindow::_closeEditor (Editor *editor)
{
    QString dir = editor->questDir();
    ResourceType type = editor->type();
    QString id = editor->id();
    _editors[type][dir].remove(id);
    _mdiArea->removeSubWindow(editor);
}

void MainWindow::_resourceContextMenu (QTreeWidgetItem* item, QPoint pos)
{
    if (item->type() != ITEM_RESOURCE) {
        return;
    }
    _treeMenu->popup(pos);
}

void MainWindow::_resourceEdit ()
{
    _openEditor(_treeWidget->currentItem(), 0);
}

void MainWindow::_resourceRemove ()
{
    QTreeWidgetItem *item = _treeWidget->currentItem();
    if (item->type() != ITEM_RESOURCE) {
        return;
    }
    if (QMessageBox::question(
        this, tr("Delete resource"),
        tr("Are you sure you want to delete this resource ?"),
        QMessageBox::Ok | QMessageBox::Cancel
    ) != QMessageBox::Ok) {
        return;
    }
    QString dir = item->data(0, ROLE_QUEST).toString();
    ResourceType type = (ResourceType)item->data(0, ROLE_TYPE).toInt();
    QString id = item->data(0, ROLE_ID).toString();
    if (_quests.contains(dir))
    {
        Quest *quest = _quests[dir];
        if (quest->removeResource(type, id)) {
            try {
                quest->save();
                if (type == SPRITE) {
                    QFile f(quest->dataDirectory() + "sprites/" + id + ".dat");
                    f.remove();
                }
            } catch (const SQCException &ex) {
                QMessageBox::warning(this, "warn", ex.message());
            }
        }
    }
}

void MainWindow::_newSprite ()
{
    _openNewResourceDialog(SPRITE);
}

void MainWindow::_openNewResourceDialog (ResourceType type)
{
    Quest *quest = _quests[_currentQuest];
    NewResourceDialog dialog(this);
    dialog.setResourceIds(quest->resourceIds(type));
    int r = dialog.exec();
    if (r == QDialog::Accepted) {
        QString id = dialog.id();
        QString name = dialog.name();
        if (type == SPRITE) {
            Sprite sprite(id, name);
            try {
                sprite.save(quest->dataDirectory());
                quest->setSprite(id, sprite);
                quest->save();
                _openEditor(quest, SPRITE, id);
            } catch (const SQCException &ex) {
                QMessageBox::warning(this, "warn", ex.message());
            }
        }
    }
}

void MainWindow::_saveResource (Editor *editor)
{
    QString dir = editor->questDir();
    ResourceType type = editor->type();
    QString id = editor->id();
    Quest *quest = _quests[dir];
    if (type == SPRITE) {
        Sprite *sprite = ((SpriteEditor *)editor)->sprite();
        try {
            if (!sprite->isSaved()) {
                sprite->save(quest->dataDirectory());
                quest->setSprite(sprite->id(), sprite->copy());
                quest->save();
            }
        } catch (const SQCException &ex) {
            QMessageBox::warning(this, "warn", ex.message());
        }
    }
}
