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
#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <QString>
#include <QList>
#include "SpriteDirection.h"

/**
 * @brief Animation d'un Sprite.
 */
class SpriteAnimation
{
public:
    /**
     * @brief Constructeur d'une animation de Sprite.
     *
     * @param name        Le nom de l'animation
     * @param image       L'image de l'animation
     * @param frameDelay  Le délais de frame
     * @param frameOnLoop Le numéro de frame de boucle
     */
    SpriteAnimation (
        QString name = "anim_0", QString image = "",
        int frameDelay = 0, int frameOnLoop = -1
    ) throw(SQCException);
    /**
     * @brief Constructeur par copie d'une animation de Sprite.
     *
     * @param other L'animation à copier
     * @param name  Le nom de la copie
     */
    SpriteAnimation (const SpriteAnimation &other, QString name);
    /**
     * @brief Donne le nom de l'animation.
     *
     * @return Le nom de l'animation.
     */
    QString name () const;
    /**
     * @brief Donne l'image de l'animation.
     *
     * @return L'image de l'animation.
     */
    QString image () const;
    /**
     * @brief Donne le délais de frame de l'animation.
     *
     * @return Le délais de frame l'animation.
     */
    int frameDelay () const;
    /**
     * @brief Donne le numéro de frame de boucle.
     *
     * @return Le numéro de frame de boucle.
     */
    int frameOnLoop () const;
    /**
     * @brief Donne le nombre de direction de l'animation.
     *
     * @return Le nombre de direction.
     */
    int countDirections () const;
    /**
     * @brief Donne une direction de l'animation.
     *
     * @param n Le numéro de la direction
     *
     * @return La direction.
     * @throw SQCException Si la direction n'existe pas.
     */
    SpriteDirection direction (const int &n) const throw(SQCException);
    /**
     * @brief Donne la liste de toutes les directions de l'animation.
     *
     * @return La liste de toutes les directions de l'animation.
     */
    QList<SpriteDirection> allDirections () const;
    /**
     * @brief Donne le nombre maximum de frame des directions de l'animation.
     *
     * @return Le nombre maximum de frame des directions.
     */
    int maxNbFrames () const;
    /**
     * @brief Change l'image de l'animation.
     *
     * @param image La nouvelle image de l'animation.
     */
    void setImage (const QString &image);
    /**
     * @brief Change le délais de frame de l'animation.
     *
     * @param frameDelay Le nouveau délais de frame de l'animation.
     *
     * @throw SQCException Si le délais est inférieur à 0.
     */
    void setFrameDelay (const int &frameDelay) throw(SQCException);
    /**
     * @brief Change la numéro de frame de boucle.
     *
     * @param frameOnLoop Le nouveau numéro de frame de boucle.
     *
     * @throw SQCException Si le numéro de frame est inférieur à -1 ou
     *         n'équivaut pas -1 dans le cas ou le délais de frame vaut 0.
     */
    void setFrameOnLoop (const int &frameOnLoop) throw(SQCException);
    /**
     * @brief Ajoute une direction à l'animation.
     *
     * @param direction La direction à ajouter
     *
     * @return Le numéro de la direction ajoutée.
     */
    int addDirection (const SpriteDirection &direction);
    /**
     * @brief Modifie une direction de l'animation.
     *
     * Si la direction n'existe pas, ou que le numéro est incorrect elle sera
     * ajoutée à la fin de la liste.
     *
     * @param n         Le numéro de la direction
     * @param direction La direction
     */
    void setDirection (const int &n, const SpriteDirection &direction);
    /**
     * @brief Supprime une direction de l'animation.
     *
     * @param n Le numéro de la direction à supprimer
     *
     * @throw SQCException Si la direction n'existe pas.
     */
    void removeDirection (const int &n) throw(SQCException);
    /**
     * @brief Intervertit deux directions de l'animation.
     *
     * @param n1 La position de la première direction
     * @param n2 La position de la deuxième direction
     *
     * @throw SQCException Si l'une des deux directions n'existe pas.
     */
    void swapDirection (const int &n1, const int &n2) throw(SQCException);
    /**
     * @brief Donne l'animation sous forme de donnée.
     *
     * @return L'animation sous forme de donnée.
     */
    QString toData () const;

private:
    QString _name;
    QString _image;
    int _frameDelay;
    int _frameOnLoop;
    QList<SpriteDirection> _directions;

    void _checkName (QString name) const throw(SQCException);
    void _checkDirectionExists (int n) const throw(SQCException);
    void _checkFrameDelay (int frameDelay) const throw(SQCException);
    void _checkFrameOnLoop (int frameOnLoop) const throw(SQCException);
};

#endif
