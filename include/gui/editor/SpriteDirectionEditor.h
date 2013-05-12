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
#ifndef SPRITE_DIRECTION_EDITOR_H
#define SPRITE_DIRECTION_EDITOR_H

#include <QWidget>
#include "sol/SpriteDirection.h"

class QSpinBox;

/**
 * @brief Editeur de direction d'animation (SpriteDirection).
 */
class SpriteDirectionEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur d'éditeur de direction d'animation.
     */
    SpriteDirectionEditor ();
    /**
     * @brief Donne la valeur de la direction d'animation.
     *
     * @return La direction d'animation.
     */
    SpriteDirection direction () const;
    /**
     * @brief Change la direction d'animation.
     *
     * @param direction La nouvelle direction d'animation
     */
    void setDirection (const SpriteDirection &direction);

signals:
    /**
     * @brief Emit lorsque la direction d'animation à terminé un changement.
     *
     * @param direction La direction d'animation
     */
    void directionChange (SpriteDirection direction);
    /**
     * @brief Emit à chaque changement direct de la direction.
     *
     * Lorsqu'un changement direct est effectué, la direction sauvegardé par
     * l'éditeur n'est pas affectée, le seul moyen de pouvoir avoir ces derniers
     * changements est d'utiliser la valeur passée en argument.
     *
     * @param direction La direction d'animation
     */
    void directDirectionChange (SpriteDirection direction);

private:
    SpriteDirection _direction;
    QSpinBox *_x;
    QSpinBox *_y;
    QSpinBox *_width;
    QSpinBox *_height;
    QSpinBox *_originX;
    QSpinBox *_originY;
    QSpinBox *_nbFrames;
    QSpinBox *_nbColumns;

    void _initWidgets ();
    void _refreshWidgets (const SpriteDirection &direction);
    void _blockSignals (bool block);

private slots:
    void _xChange ();
    void _yChange ();
    void _widthChange ();
    void _heightChange ();
    void _originXChange ();
    void _originYChange ();
    void _nbFramesChange ();
    void _nbColumnsChange ();

    void _directXChange ();
    void _directYChange ();
    void _directWidthChange ();
    void _directHeightChange ();
    void _directOriginXChange ();
    void _directOriginYChange ();
    void _directNbFramesChange ();
    void _directNbColumnsChange ();
};

#endif
