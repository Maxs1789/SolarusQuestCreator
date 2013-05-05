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
#ifndef ACTION_H
#define ACTION_H

#include <QString>

/** Type d'action de base. */
#define BASIC_ACTION 0

/**
 * @brief Classe abstaite de base pour les actions.
 *
 * @see Model
 */
class Action
{
public:
    /**
     * @brief Exécute l'action.
     */
    virtual void execute () = 0;
    /**
     * @brief Annule l'action.
     */
    virtual void reverse () = 0;
    /**
     * @brief Donne le type de l'action.
     *
     * @return Le type de l'action.
     */
    int type () const
    {
        return _type;
    }
    /**
     * @brief Vérifie si l'action est de type basique.
     * 
     * @return `true` si elle est de type basique, `false` sinon.
     */
    bool isBasicAction () const
    {
        return _type == BASIC_ACTION;
    }
    /**
     * @brief Donne le message de l'action destiné aux vues.
     *
     * @return Le message de l'action.
     */
    QString message () const
    {
        return _message;
    }

protected:
    /** Le message de l'action detiné aux vues. */
    QString _message;

    /**
     * @brief Constructeur d'action.
     *
     * @param type    Le type de l'action
     * @param message Le message de l'action destiné aux vues
     */
    Action (QString message = "", int type = BASIC_ACTION) :
        _type(type),
        _message(message)
    {}    

private:
    int _type;
};

#endif
