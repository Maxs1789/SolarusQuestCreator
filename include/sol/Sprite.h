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
#ifndef SPRITE_H
#define SPRITE_H

#include <QMap>
#include <lua.hpp>
#include "base/Model.h"
#include "view/SpriteView.h"
#include "exception/IOException.h"
#include "Resource.h"
#include "SpriteSelection.h"
#include "SpriteAnimation.h"

/**
 * @brief Ressource de type Sprite.
 *
 * @see ResourceType, SpriteView
 */
class Sprite : public Resource, public Model<SpriteView>
{
public:
    /** Constante de notification pour les sous modèles `animation`. */
    static const QString p_animation;
    /**
     * @brief Charge un Sprite.
     *
     * @param dataDirectory Le dossier de travail d'une quete (Quest)
     * @param id            L'identifiant du Sprite
     * @param name          Le nom à assigner au Sprite
     *
     * @return Le Sprite chargé.
     * @throw SQCException Si le fichier ne peut etre lu.
     */
    static Sprite *load (QString dataDirectory, QString id, QString name)
        throw(SQCException);
    /**
     * @brief Constructeur de Sprite.
     *
     * @param id   L'identifiant du Sprite
     * @param name Le nom du Sprite
     */
    Sprite (QString id, QString name = "new sprite");
    /**
     * @brief Vérifie que le Sprite est à l'état de sauvegarde.
     *
     * @return `true` si le Sprite est à l'état de sauvegarde, `false` sinon.
     */
    bool isSaved () const;
    /**
     * @brief Sauvegarde un Sprite dans un dossier de quete (Quest)
     *
     * @param dataDirectory Le dossier de travail de la quete.
     */
    void save (QString dataDirectory) throw(SQCException);
    /**
     * @brief Copie un Sprite.
     *
     * Cette méthode est nécessaire pour avoir un Sprite qui est vidé de toute
     * actions.
     *
     * @return La copie du Sprite.
     */
    Sprite copy () const;
    /**
     * @brief Vérifie qu'une animation existe.
     *
     * @param name Le nom de l'animation
     *
     * @return `true` si l'animation existe, `false` sinon.
     */
    bool animationExists (QString name) const;
    /**
     * @brief Donne une animation du Sprite.
     *
     * @param name Le nom de l'animation
     *
     * @return L'animation.
     * @throw SQCException Si l'animation n'existe pas.
     */
    SpriteAnimation animation (QString name) const throw(SQCException);
    /**
     * @brief Donne une liste d'animation du Sprite.
     *
     * @param names La liste des noms d'animation désiré.
     *
     * @return La liste des animations correspondante.
     */
    QList<SpriteAnimation> animations (QList<QString> names) const;
    /**
     * @brief Donne la liste de nom de toutes les animations du Sprite.
     *
     * @return La liste de nom des animations.
     */
    QList<QString> animationNames () const;
    /**
     * @brief Donne la liste de toutes les animations du Sprite.
     *
     * @return la liste de toutes les animations.
     */
    QList<SpriteAnimation> allAnimations () const;
    /**
     * @brief Donne la sélection du Sprite.
     *
     * @return La sélection.
     */
    SpriteSelection selection () const;
    /**
     * @brief Donne le nom du fichier de donnée du Sprite.
     *
     * @return Le nom du fichier de donnée.
     */
    QString filename () const;
    /**
     * @brief Renomme le Sprite.
     *
     * @param name Le nouveau nom
     */
    void setName (QString name);
    /**
     * @brief Supprime une animation du Sprite.
     *
     * @param name Le nom de l'animation à supprimer
     *
     * @return `true` si l'animation à été suppriméé, `false` sinon.
     */
    bool removeAnimation (QString name);
    /**
     * @brief Modifie une animation du Sprite.
     *
     * Si l'animation n'existe pas, elle sera ajoutée.
     *
     * @param name      Le nom de l'animation à modifier
     * @param animation L'animation
     */
    void setAnimation (QString name, const SpriteAnimation &animation);
    /**
     * @brief Renomme une animation du Sprite.
     *
     * @param name    Le nom du l'animation à changer
     * @param newName Le nouveau nom à lui donner
     */
    void renameAnimation (QString name, QString newName) throw(SQCException);
    /**
     * @brief Change la sélection du Sprite.
     *
     * @param selection La sélection à donner au Sprite.
     */
    void setSelection (const SpriteSelection &selection) throw(SQCException);

protected:
    void onActionNotify (Action *action, SpriteView *view);
    void onUserNotify (int userType, SpriteView *view);

private:
    QMap<QString, SpriteAnimation> _animations;
    SpriteSelection _selection;

    QString _setName (QString name);
    SpriteAnimation _setAnimation (QString name, SpriteAnimation animation);
    void _addAnimations (
        QList<QString> names, QList<SpriteAnimation> animations
    );
    QList<SpriteAnimation> _removeAnimations (QList<QString> names);
    void _renameAnimation (QString oldName, QString newName);

    void _checkAnimationExists (QString name) const throw(SQCException);
    void _checkAnimationNExists (QString name) const throw(SQCException);
    void _checkSelection (const SpriteSelection &selection) const
        throw(SQCException);
};

#endif
