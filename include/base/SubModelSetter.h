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
#ifndef SUB_MODEL_SETTER_H
#define SUB_MODEL_SETTER_H

#include "Action.h"

/**
 * @brief Classe d'assignation d'un sous modèle.
 *
 * Cette classe à trois paramètres template qui représentant le type du modèle
 * que modifie l'action, le type du sous modèle à assigner et le type de
 * l'identifiant de ce sous modèle.
 */
template<typename type_Model, typename type_SubModel, typename type_Id>
class SubModelSetter : public Action
{
public:
    /**
     * @brief Constructeur d'assignateur de sous modèle.
     *
     * @param model        Le modèle à éditer
     * @param propertyName Nom de propriété pour la notification
     * @param set          La méthode d'assignation du modèle
     * @param id           L'identifiant du sous modèle à assigner
     * @param value        Le sous modèle à assigner
     * @param type         Le type de l'action
     */
    SubModelSetter (
        type_Model *model, QString propertyName,
        type_SubModel (type_Model::*set)(type_Id, type_SubModel),
        type_Id id, type_SubModel value, int type = BASIC_ACTION
    ) :
        Action(propertyName, type),
        _model(model),
        _id(id),
        _value(value),
        _set(set)
    {}

    void execute ()
    {
        _value = (_model->*_set)(_id, _value);
    }

    void reverse ()
    {
        _value = (_model->*_set)(_id, _value);
    }
    /**
     * @brief Donne l'identifiant du sous modèle assigné.
     *
     * @return L'identifiant du sous modèle assigné.
     */
    type_Id id () const
    {
        return _id;
    }

private:
    type_Model *_model;
    type_Id _id;
    type_SubModel _value;
    type_SubModel (type_Model::*_set)(type_Id, type_SubModel);
};

#endif
