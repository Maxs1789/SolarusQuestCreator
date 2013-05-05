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
#ifndef SPRITE_EDITOR_H
#define SPRITE_EDITOR_H

#include "gui/Editor.h"
#include "sol/Sprite.h"

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QGraphicsView;
class QListWidget;
class QGroupBox;
class SQCGraphicsView;
class SpriteAnimationEditor;
class SpriteDirectionEditor;
class SpriteDirectionPreview;

class SpriteEditor : public Editor, public SpriteView
{
    Q_OBJECT
public:
    SpriteEditor (Quest *quest, const Sprite &sprite);
    ~SpriteEditor ();

    Sprite *sprite ();

    void simpleRefresh (QString message);
    void refreshSelection (const SpriteSelection &selection);
    void refreshAnimation (const QString &name);
    void addAnimation (const QString &name);
    void removeAnimation (const QString &name);
    void renameAnimation (const QString &oldName, const QString &newName);

protected:
    bool isSaved () const;

private:
    Quest *_quest;
    Sprite *_sprite;
    QLabel *_id;
    QLineEdit *_name;
    QComboBox *_animations;
    SQCGraphicsView *_graphicsView;
    SpriteAnimationEditor *_animationEditor;
    QListWidget *_directions;
    SpriteDirectionEditor *_directionEditor;
    QPushButton *_addAnimationButton;
    QPushButton *_removeAnimationButton;
    QPushButton *_addDirectionButton;
    QPushButton *_removeDirectionButton;
    QPushButton *_upDirectionButton;
    QPushButton *_downDirectionButton;
    QAction *_actionUndo;
    QAction *_actionRedo;
    QAction *_actionSave;
    QGroupBox *_animationGroup;
    SpriteDirectionPreview *_directionPreview;

    void _initWidgets ();
    void _connects ();
    void _refreshWidgets ();

    void _refreshTitle ();
    void _swapDirection (const int &n1, const int &n2);

private slots:
    void _nameChange ();
    void _animationSelectionChange ();
    void _animationRename ();
    void _animationChange (SpriteAnimation animation);
    void _tilesetChange ();
    void _addAnimation ();
    void _removeAnimation ();
    void _directionSelectionChange ();
    void _directionChange (SpriteDirection direction);
    void _addDirection ();
    void _removeDirection ();
    void _upDirection ();
    void _downDirection ();

    void _save ();

    void _undo ();
    void _redo ();
};

#endif
