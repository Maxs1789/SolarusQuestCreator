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
#ifndef SETTER_H
#define SETTER_H

#include "Action.h"

/**
 * @brief Classe d'assignation de propriété d'un modèle.
 *
 * Cette classe à deux paramètres template représentant le type de modèle que
 * modifie l'action et le type de la propriété éditée.
 */
template<typename type_Model, typename type_Property>
class Setter : public Action
{
public:
    /**
     * @brief Constructeur d'assignateur.
     *
     * @param model        Le modèle à éditer
     * @param propertyName Le nom de la propriété pour la notification
     * @param set          La méthode d'assignation du modèle
     * @param value        La nouvelle valeur de la propriété
     * @param type         Le type de l'action
     */
    Setter (
        type_Model *model, QString propertyName,
        type_Property (type_Model::*set)(type_Property), type_Property value,
        int type = BASIC_ACTION
    ) :
        Action(propertyName, type),
        _model(model),
        _value(value),
        _set(set)
    {}

    void execute ()
    {
        _value = (_model->*_set)(_value);
    }

    void reverse ()
    {
        _value = (_model->*_set)(_value);
    }

private:
    type_Model *_model;
    type_Property _value;
    type_Property (type_Model::*_set)(type_Property);
};

#endif
