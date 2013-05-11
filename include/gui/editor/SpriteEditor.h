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
class QSpinBox;
class ColorButton;
class SpriteGraphicsView;
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

    bool isSaved () const;
    void save (QString dataDirectory) throw(SQCException);

private:
    Quest *_quest;
    Sprite *_sprite;
    QLabel *_id;
    QLineEdit *_name;
    QComboBox *_animations;
    SpriteGraphicsView *_graphicsView;
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
    QGroupBox *_directionGroup;
    SpriteDirectionPreview *_directionPreview;
    int _animCount;
    QPixmap _currentImage;
    ColorButton *_selColor;
    ColorButton *_backColor;
    QComboBox *_graphicsViewZoom;
    QAction *_actionSceneBorder;
    QAction *_actionShowGrid;
    QAction *_actionSnapGrid;
    QSpinBox *_gridWidth;
    QSpinBox *_gridHeight;

    void _initWidgets ();
    void _initToolBar ();
    void _connects ();
    void _firstRefresh ();

    void _refreshTitle ();
    void _refreshDirections (const QList<SpriteDirection> &directions);
    QString _directionName (const int &dir, const int &n);
    void _setCurrentImage (QString imagePath);
    void _refreshDirectionEditor (
        const int &n, const SpriteDirection &direction
    );
    void _refreshDirectionPreview (
        const SpriteAnimation &animation, const SpriteDirection &direction
    );
    void _swapDirection (const int &n1, const int &n2);
    void _addDirection (Rect selection);

private slots:
    void _nameChange ();
    void _animationSelectionChange ();
    void _animationRename ();
    void _animationChange (SpriteAnimation animation);
    void _tilesetChange ();
    void _addAnimation ();
    void _removeAnimation ();
    void _directionSelectionChange ();
    void _directionNewSelection (Rect selection);
    void _directionChange (SpriteDirection direction);
    void _directAnimationChange (SpriteAnimation animation);
    void _directDirectionChange (SpriteDirection direction);

    void _addDirection ();
    void _removeDirection ();
    void _upDirection ();
    void _downDirection ();

    void _save ();

    void _undo ();
    void _redo ();

    void _graphicsViewSetZoom (float zoom);
    void _graphicsViewZoomChange ();

    void _snapEnabled (bool enable);

    void _backColorChange (QColor color);
};

#endif
