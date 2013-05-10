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
#ifndef SPRITE_ANIMATION_EDITOR_H
#define SPRITE_ANIMATION_EDITOR_H

#include <QWidget>
#include "sol/SpriteAnimation.h"

class QLineEdit;
class QSpinBox;
class QListWidget;
class QPushButton;
class QStackedWidget;
class Quest;
class SpriteDirectionEditor;
class ImageFinder;
class TilesetComboBox;

class SpriteAnimationEditor : public QWidget
{
    Q_OBJECT
public:
    SpriteAnimationEditor (Quest *quest);

    SpriteAnimation animation () const;

    QString tileset () const;

    void setAnimation (const SpriteAnimation &animation);

signals:
    void animationChange (SpriteAnimation animation);
    void tilesetChange ();

    void directAnimationChange (SpriteAnimation animation);

private:
    Quest *_quest;
    QString _directory;
    SpriteAnimation _animation;
    QLineEdit *_image;
    QSpinBox *_frameDelay;
    QSpinBox *_frameOnLoop;
    QPushButton *_imageButton;
    ImageFinder *_imageFinder;
    TilesetComboBox *_tilesetComboBox;
    QStackedWidget *_imageWidget;

    void _initWidgets ();
    void _refreshWidgets (const SpriteAnimation &animation);
    void _blockSignals (bool block);

private slots:
    void _imageChange ();
    void _frameDelayChange ();
    void _frameOnLoopChange ();
    void _findImage ();
    void _tilesetChange ();

    void _directFrameDelayChange ();
    void _directFrameOnLoopChange ();
};

#endif
