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
#ifndef TILE_PATTERN_H
#define TILE_PATTERN_H

#include <QString>
#include "types.h"
#include "exception/SQCException.h"

/**
 * @brief Tile Pattern d'un Tileset.
 */
class TilePattern
{
public:
    /**
     * @brief Constructeur de Tile Pattern par défaut.
     *
     * @param id L'identifiant du Pattern
     */
    TilePattern (int id = -1);
    /**
     * @brief Constructeur de Tile Pattern.
     *
     * @param x      La position en x de la première frame du Pattern
     * @param y      La position en y de la première frame du Pattern
     * @param width  La largeur du Pattern
     * @param height La hauteur du Pattern
     * @param id     L'identifiant du Pattern
     *
     * @throw SQCException Si les coordonnées ou les dimensions sont
     *         incorrectes.
     */
    TilePattern (int x, int y, int width, int height, int id = -1)
        throw(SQCException);
    /**
     * @brief Constructeur de Tile Pattern par copie.
     *
     * @param other Le Pattern à copier
     * @param id    L'identifiant du Pattern
     */
    TilePattern (const TilePattern &other, int id);
    /**
     * @brief Donne l'identifiant du Pattern.
     *
     * @return L'identifiant du Pattern.
     */
    int id () const;
    /**
     * @brief Donne le type d'obstacle du Pattern.
     *
     * @return Le type d'obstacle du Pattern.
     */
    Ground ground () const;
    /**
     * @brief Donne la couche par défaut du Pattern.
     *
     * @return La couche par défaut du Pattern.
     */
    Layer defaultLayer () const;
    /**
     * @brief Donne le type de défilement du Pattern.
     *
     * @return Le type de défilement du Pattern.
     */
    Scrolling scrolling () const;
    /**
     * @brief Donne la largeur du Pattern.
     *
     * @return La largeur du Pattern.
     */
    int width () const;
    /**
     * @brief Donne la hauteur du Pattern.
     *
     * @return La hauteur du Pattern.
     */
    int height () const;
    /**
     * @brief Donne la position en x de la première frame du Pattern.
     *
     * @return La position en x de la première frame du Pattern.
     */
    int x () const;
    /**
     * @brief Donne la position en y de la première frame du Pattern.
     *
     * @return La position en y de la première frame du Pattern.
     */
    int y () const;
    /**
     * @brief Donne la position en x de la deuxième frame du Pattern.
     *
     * @return La position en x de la deuxième frame du Pattern ou `-1` dans le
     * cas ou le tile n'est pas animé.
     *
     * @see isAnimated
     */
    int x2 () const;
    /**
     * @brief Donne la position en y de la deuxième frame du Pattern.
     *
     * @return La position en y de la deuxième frame du Pattern ou `-1` dans le
     * cas ou le tile n'est pas animé.
     *
     * @see isAnimated
     */
    int y2 () const;
    /**
     * @brief Donne la position en x de la troisième frame du Pattern.
     *
     * @return La position en x de la troisième frame du Pattern ou `-1` dans le
     * cas ou le tile n'est pas animé.
     *
     * @see isAnimated
     */
    int x3 () const;
    /**
     * @brief Donne la position en y de la troisième frame du Pattern.
     *
     * @return La position en y de la troisième frame du Pattern ou `-1` dans le
     * cas ou le tile n'est pas animé.
     *
     * @see isAnimated
     */
    int y3 () const;
    /**
     * @brief Donne le type de la séquence d'animation du Pattern.
     *
     * @return `true` si la séquence est de type `0-1-2-1-0-...`, false sinon.
     * Dans le cas ou le tile n'est pas animé cette méthode renverra toujours
     * `false`.
     *
     * @see isAnimated
     */
    bool isSeq0121 () const;
    /**
     * @brief Vérifie que le Pattern de tile est animé.
     *
     * @return `true` si le tile est animé, `false`sinon.
     *
     * @see setPosition, setPositions
     */
    bool isAnimated () const;
    /**
     * @brief Modifie le type d'obstacle du Pattern.
     *
     * @param ground Le nouveau type d'obstacle
     */
    void setGround (Ground ground);
    /**
     * @brief Modifie la couche par défaut du Pattern.
     *
     * @param defaultLayer La nouvelle couche
     */
    void setDefaultLayer (Layer defaultLayer);
    /**
     * @brief Modifie le type de défilement du Pattern.
     *
     * @param scrolling Le nouveau type de défilement
     */
    void setScrolling (Scrolling scrolling);
    /**
     * @brief Modifie la largeur du Pattern.
     *
     * La largeur doit être multiple de 8 et plus grand que 0.
     *
     * @param width La nouvelle largeur.
     *
     * @throw SQCException Si la largeur est incorrecte.
     */
    void setWidth (int width) throw(SQCException);
    /**
     * @brief Modifie la hauteur du Pattern.
     *
     * La hauteur doit âtre multiple de 8 et plus grand que 0.
     *
     * @param height La nouvelle hauteur
     *
     * @throw SQCException Si la hauteur est incorrecte.
     */
    void setHeight (int height) throw(SQCException);
    /**
     * @brief Modifie la position de la première frame du Pattern.
     *
     * Cette méthode ne garde que la première frame, le tile ne sera donc plus
     * animé.
     * Les coordonnées x et y doivent être multiples de 8 et plus grandes que 0.
     *
     * @param x La nouvelle position en x de la première frame
     * @param y La nouvelle position en y de la première frame
     *
     * @throw SQCException Si les coordonnées sont incorrectes.
     * @see setPositions
     */
    void setPosition (int x, int y) throw(SQCException);
    /**
     * @brief Modifie la positions des frames du Pattern.
     *
     * Toutes les coordonnées doivent être multiples de 8 et plus grandes que 0.
     *
     * @param x1      La nouvelle position en x de la première frame
     * @param y1      La nouvelle position en y de la première frame
     * @param x2      La nouvelle position en x de la deuxième frame
     * @param y2      La nouvelle position en y de la deuxième frame
     * @param x3      La nouvelle position en x de la troisième frame
     * @param y3      La nouvelle position en y de la troisième frame
     * @param seq0121 Le nouveau type de séquence d'animation.
     *
     * @throw SQCException Si les coordonnées sont incorrectes.
     * @see isSeq0121
     */
    void setPositions (
        int x1, int y1, int x2, int y2,
        int x3, int y3, bool seq0121 = false
    ) throw(SQCException);
    /**
     * @brief Donne une chaîne contenant le code lua correspondant au Pattern.
     *
     * @return La chaîne de code lua.
     */
    QString toLua () const;

private:
    struct Positions
    {
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
        bool seq0121;
    };

    int _id;
    Ground _ground;
    Layer _defaultLayer;
    Scrolling _scrolling;
    Positions _positions;
    int _width;
    int _height;

    void _checkWidth (const int &width) const throw(SQCException);
    void _checkHeight (const int &height) const throw(SQCException);
    void _checkXY (const int &x, const int &y) const
        throw(SQCException);
    void _checkPositions (
        const int &x1, const int &y1, const int &x2,
        const int &y2, const int &x3, const int &y3
    ) const throw(SQCException);
    QString _groundToString (Ground ground) const;
    QString _scrollingToString (Scrolling scrolling) const;
};

#endif
