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
#ifndef SPRITE_DIRECTION_H
#define SPRITE_DIRECTION_H

#include "exception/SQCException.h"
#include "sol/types.h"

/**
 * @brief Direction d'une animation d'un Sprite (SpriteAnimation).
 */
class SpriteDirection
{
public:
    /**
     * @brief Constructeur d'une direction d'animation.
     *
     * @param x         La coordonnée x
     * @param y         La coordonnée y
     * @param width     La largeur
     * @param height    La hauteur
     * @param originX   La coordonnée x de l'origine
     * @param originY   La coordonnée y de l'origine
     * @param nbFrames  Le nombre de frames
     * @param nbColumns Le nombre de colonnes
     */
    SpriteDirection (
        int x = 0, int y = 0, int width = 24, int height = 24,
        int originX = 12, int originY = 12, int nbFrames = 1, int nbColumns = 1
    ) throw (SQCException);
    /**
     * @brief Constructeur d'une direction d'animation.
     *
     * @param dimension Les dimensions de la direction
     * @param originX   La coordonnée x de l'origine
     * @param originY   La coordonnée y de l'origine
     * @param nbFrames  Le nombre de frames
     * @param nbColumns Le nombre de colonnes
     */
    SpriteDirection (Rect dimension, int nbFrames = 1, int nbColumns = 1)
        throw (SQCException);
    /**
     * @brief Opérateur de différence d'un direction.
     *
     * @param other La direction à comparer
     *
     * @return `true` si les directions sont différentes, `false` sinon.
     */
    bool operator!= (const SpriteDirection &other);
    /**
     * @brief Donne la coordonnée x de la direction.
     *
     * @return La coordonnée x.
     */
    int x () const;
    /**
     * @brief Donne la coordonnée y de la direction.
     *
     * @return La coordonnée y.
     */
    int y () const;
    /**
     * @brief Donne la largeur de la direction.
     *
     * @return La largeur.
     */
    int width () const;
    /**
     * @brief Donne la hauteur de la direction.
     *
     * @return La hauteur.
     */
    int height () const;
    /**
     * @brief Donne la coordonnée x de l'origine de la direction.
     *
     * @return La coordonnée x de l'origine.
     */
    int originX () const;
    /**
     * @brief Donne la coordonnée y de l'origine de la direction.
     *
     * @return La coordonnée y de l'origine.
     */
    int originY() const;
    /**
     * @brief Donne le nombre de frames de la direction.
     *
     * @return Le nombre de frames.
     */
    int nbFrames() const;
    /**
     * @brief Donne le nombre de colonnes de la direction.
     *
     * @return Le nombre de colonnes.
     */
    int nbColumns () const;
    /**
     * @brief Modifie la coordonnée x de la direction.
     *
     * @param x La nouvelle coordonnée x
     *
     * @throw SQCException Si la coordonnée est inférieure à 0.
     */
    void setX (const int &x) throw (SQCException);
    /**
     * @brief Modifie la coordonnée y de la direction.
     *
     * @param y La nouvelle coordonnée y
     *
     * @throw SQCException Si la coordonnée est inférieure à 0.
     */
    void setY (const int &y) throw (SQCException);
    /**
     * @brief Modifie la largeur de la direction.
     *
     * @param width La nouvelle largeur
     *
     * @throw SQCException Si la largeur est inférieure à 1.
     */
    void setWidth (const int &width) throw (SQCException);
    /**
     * @brief Modifie la hauteur de la direction.
     *
     * @param height La nouvelle hauteur
     *
     * @throw SQCException Si la hauteur est inférieure à 1.
     */
    void setHeight (const int &height) throw (SQCException);
    /**
     * @brief Modifie la coordonnée x de l'origine de la direction.
     *
     * @param originX La nouvelle coordonnée x de l'origine
     */
    void setOriginX (const int &originX);
    /**
     * @brief Modifie la coordonnée y de l'origine de la direction.
     *
     * @param originY La nouvelle coordonnée y de l'origine
     */
    void setOriginY (const int &originY);
    /**
     * @brief Modifie le nombre de frames de la direction.
     *
     * @param nbFrames Le nouveau nombre de frames
     *
     * @throw SQCException Si le nombre de frames est inférieur à 1.
     */
    void setNbFrames (const int &nbFrames) throw (SQCException);
    /**
     * @brief Modifie le nombre de colonnes de la direction.
     *
     * @param nbColumns Le nouveau nombre de colonnes
     *
     * @throw SQCException Si le nombre de colonnes est inférieur à 1.
     */
    void setNbColumns (const int &nbColumns) throw (SQCException);

private:
    int _x, _y, _width, _height, _originX, _originY, _nbFrames, _nbColumns;

    void _checkX (const int &x) const throw (SQCException);
    void _checkY (const int &y) const throw (SQCException);
    void _checkWidth (const int &width) const throw (SQCException);
    void _checkHeight (const int &height) const throw (SQCException);
    void _checkNbFrames (const int &nbFrames) const throw (SQCException);
    void _checkNbColumns (const int &nbColumns) const throw (SQCException);
};

#endif
