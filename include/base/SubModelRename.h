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
#ifndef SUB_MODEL_RENAME_H
#define SUB_MODEL_RENAME_H

#include "Action.h"

#define RENAME_ACTION 2

/**
 * @brief Classe de renommage d'un sous modèle (changement d'id).
 *
 * Cette classe à deux paramètres template qui représentant le type du modèle
 * que modifie l'action et le type de l'identifiant de ce sous modèle.
 */
template<typename type_Model, typename type_Id>
class SubModelRename : public Action
{
public:
    /**
     * @brief Constructeur du renommeur de sous modèle.
     *
     * @param model        Le modèle à éditer
     * @param propertyName Nom de propriété pour la notification
     * @param rename       La méthode de renommage du modèle
     * @param oldId        L'ancien identifiant du sous modèle
     * @param newId        Le nouvel identifiant du sous modèle
     * @param type         Le type de l'action
     */
    SubModelRename (
        type_Model *model, QString propertyName,
        void (type_Model::*rename)(type_Id, type_Id),
        type_Id oldId, type_Id newId, int type = RENAME_ACTION
    ) :
        Action(propertyName, type),
        _model(model),
        _old(newId),
        _new(oldId),
        _rename(rename)
    {}

    void execute ()
    {
        type_Id tmp = _old;
        _old = _new;
        _new = tmp;
        (_model->*_rename)(_old, _new);
    }

    void reverse ()
    {
        type_Id tmp = _old;
        _old = _new;
        _new = tmp;
        (_model->*_rename)(_old, _new);
    }
    /**
     * @brief Donne l'ancien identifiant du sous modèle.
     *
     * @return L'ancien identifiant du sous modèle.
     */
    type_Id oldId () const
    {
        return _old;
    }
    /**
     * @brief Donne le nouvel identifiant du sous modèle.
     *
     * @return Le nouvel identifiant du sous modèle.
     */
    type_Id newId () const
    {
        return _new;
    }

private:
    type_Model *_model;
    type_Id _old;
    type_Id _new;
    void (type_Model::*_rename)(type_Id, type_Id);
};

#endif
