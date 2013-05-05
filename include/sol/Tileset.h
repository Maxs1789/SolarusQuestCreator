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
#ifndef TILESET_H
#define TILESET_H

#include <QMap>
#include <lua.hpp>
#include "base/Model.h"
#include "view/TilesetView.h"
#include "exception/SQCException.h"
#include "Resource.h"
#include "TilePattern.h"

/**
 * @brief Ressource de type Tileset.
 *
 * @see ResourceType, TilesetView
 */
class Tileset : public Resource, public Model<TilesetView>
{
public:
    /** Constante de notification pour la proriété `backgroundColor`. */
    static const QString p_backgroundColor;
    /** Constante de notification pour les sous modèles `tilePattern`. */
    static const QString p_tilePattern;

    static Tileset *load (QString dataDirectory, QString id, QString name)
        throw(SQCException);

    /**
     * @brief Constructeur de Tileset.
     *
     * @param id   L'identifiant du Tileset
     * @param name Le nom du Tileset
     */
    Tileset (QString id, QString name = "new tileset");

    Tileset copy () const;
    /**
     * @brief Donne la couleur de fond du Tileset.
     *
     * @return La couleur de fond du Tileset.
     */
    Color backgroundColor () const;
    /**
     * @brief Vérifie qu'un Tile Pattern existe.
     *
     * @param id L'identifiant du Tile Pattern
     *
     * @return `true` si le Tile Pattern existe, `false` sinon.
     */
    bool patternExists (int id) const;
    /**
     * @brief Donne un Tile Pattern.
     *
     * @param id L'identifiant du Tile Pattern
     *
     * @return Le Tile Pattern.
     *
     * @throw TilePatternException Si le Tile Pattern n'existe pas.
     */
    TilePattern pattern (int id) const throw(SQCException);
    /**
     * @brief Donne une liste de Tile Pattern.
     *
     * Les identifiants qui ne correspondent à aucun Tile Pattern existant
     * seront ignoré.
     *
     * @param ids La liste des identifiants de Tile Pattern
     *
     * @return La liste des Tile Pattern.
     */
    QList<TilePattern> patterns (QList<int> ids) const;
    /**
     * @brief Donne la liste de tout les identifiants de Tile Pattern.
     *
     * @return La liste de tout les identifiants de Tile Pattern.
     */
    QList<int> patternIds () const;
    /**
     * @brief Donne la liste de tout les Tile Pattern.
     *
     * @return La liste de tout les Tile Pattern.
     */
    QList<TilePattern> allPatterns () const;
    /**
     * @brief Donne la liste des Tile Pattern de la sélection.
     *
     * @return La liste des Tile Pattern de la sélection.
     *
     * @see patterns, selection
     */
    QList<TilePattern> patternSelection () const;
    /**
     * @brief Vérifie qu'il y a une sélection.
     *
     * @return `true` si il y a une sélection, `false` sinon.
     */
    bool haveSelection () const;
    /**
     * @brief Donne la sélection courante.
     *
     * @return La sélection courante.
     */
    QList<int> selection () const;
    /**
     * @brief Donne le nom du fichier de données du Tileset.
     *
     * @return Le nom du fichier de données.
     */
    QString filename () const;

    void setName (QString name);
    /**
     * @brief Modifie la couleur de fond du tileset.
     *
     * @param color La nouvelle couleur de fond
     */
    void setBackgroundColor (Color color);
    /**
     * @brief Ajoute un Tile Pattern.
     *
     * L'identifiant du Pattern passé en paramètre n'est pas pris en compte, un
     * identifiant unique et valide lui est attribué; celui-ci est retourné.
     *
     * @param pattern Le Tile Pattern à ajouter
     *
     * @return L'identifiant assigner au Tile Pattern.
     */
    int addPattern (const TilePattern &pattern);
    /**
     * @brief Ajoute des Tile Pattern.
     *
     * Les identifiants des Pattern passés en paramètre ne sont pas pris en
     * compte, de nouveaux identifiants leurs sont attribués; ceux-ci sont
     * retournés sous forme de liste.
     *
     * @param patterns La liste des Tile Pattern à ajouter
     *
     * @return La liste des identifiants attribués.
     */
    QList<int> addPatterns (QList<TilePattern> patterns);
    /**
     * @brief Supprime un Tile Pattern.
     *
     * @param id L'identifiant du Tile Pattern à supprimer
     *
     * @return `true` Si il a pu être supprimé, `false` sinon (n'existait pas).
     */
    bool removePattern (int id);
    /**
     * @brief Supprime des Tile Pattern.
     *
     * @param ids La liste des identifiants de Tile Pattern à supprimer
     *
     * @throw SQCException Si l'un des Pattern n'existe pas.
     */
    void removePatterns (QList<int> ids) throw(SQCException);
    /**
     * @brief Supprime les Tile Pattern de la sélection.
     *
     * @return `true` Si la sélection a pu être supprimée, `false` sinon (vide).
     */
    bool removeSelectionPatterns () throw(SQCException);
    /**
     * @brief Modifie un Tile Pattern.
     *
     * @param id      L'identifiant du Tile Pattern à modifier
     * @param pattern Le nouveau Tile Pattern
     */
    void setPattern (int id, const TilePattern &pattern);
    /**
     * @brief Ajout un Tile Pattern à la sélection.
     *
     * @param id L'identifiant du Tile Pattern à ajouter
     */
    void selectPattern (int id);
    /**
     * @brief Retire un Tile Pattern de la sélection.
     *
     * @param id L'identifiant du Tile Pattern à retirer
     */
    void unselectPattern (int id);

protected:
    void onActionNotify (Action *action, TilesetView *view);
    void onUserNotify (int userType, TilesetView *view);

private:
    Color _backgroundColor;
    QMap<int, TilePattern> _tilePatterns;
    QList<int> _selection;
    int _uniquePatternId;

    QString _setName (QString name);
    Color _setBackgroundColor (Color color);
    TilePattern _setPattern (int id, TilePattern pattern);
    void _addPatterns (QList<int> ids, QList<TilePattern> patterns);
    QList<TilePattern> _removePatterns (QList<int> ids);

    void _checkPatternExists (int id) const throw(SQCException);

    static int _lua_backgroundColor (lua_State *L);
    static int _lua_tilePattern (lua_State *L);
    static Ground _checkGround (lua_State *L, int index);
};

#endif
