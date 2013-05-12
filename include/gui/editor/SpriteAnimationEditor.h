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

/**
 * @brief Editeur d'animation de Sprite (SpriteAnimation).
 */
class SpriteAnimationEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur d'éditeur d'animation de Sprite.
     *
     * L'éditeur à besoin de la quete pour pouvoir retrouver les tilesets.
     *
     * @param quest La quete dans laquelle se trouve l'animation
     *
     * @see Quest, Tileset
     */
    SpriteAnimationEditor (Quest *quest);
    /**
     * @brief Donne l'animation de Sprite.
     *
     * @return L'animation de Sprite.
     */
    SpriteAnimation animation () const;
    /**
     * @brief Donne l'identifiant du tileset sélectionné.
     *
     * Un tileset peut etre sélectionné si le nom de l'image de l'animation
     * correspond à `tileset`.
     *
     * @return L'identifiant du tileset sélectionné.
     * @see Tileset
     */
    QString tileset () const;
    /**
     * @brief Change l'animation de Sprite.
     *
     * @param animation La nouvelle animation de Sprite.
     */
    void setAnimation (const SpriteAnimation &animation);

signals:
    /**
     * @brief Emit lorsque l'animation à terminé un changement.
     *
     * @param animation L'animation
     */
    void animationChange (SpriteAnimation animation);
    /**
     * @brief Emit lorsqu'un Tileset est sélectioné.
     */
    void tilesetChange ();
    /**
     * @brief Emit à chaque changement direct de l'animation.
     *
     * Lorsqu'un changement direct est effectué, l'animation sauvegardé par
     * l'éditeur n'est pas affectée, le seul moyen de pouvoir avoir ces derniers
     * changements est d'utiliser la valeur passée en argument.
     *
     * @param animation L'animation
     */
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
