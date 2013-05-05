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
#ifndef REMOVER_H
#define REMOVER_H

#include "GroupAction.h"

/**
 * @brief Classe de suppression de sous modèles.
 *
 * Cette classe à trois paramètres template qui représentant le type du modèle
 * que modifie l'action, le type du sous modèle à supprimer et le type de
 * l'identifiant de ce sous modèle.
 */
template<typename type_Model, typename type_SubModel, typename type_Id>
class Remover : public GroupAction<type_Id>
{
public:
    /**
     * @brief Constructeur d'action de suppression de sous modèles.
     *
     * @param model        Le modèle à éditer
     * @param propertyName Le nom de la propriété pour la notification
     * @param remove       La méthode de suppression du modèle
     * @param add          La méthode d'ajout du modèle
     * @param ids          Liste des identifiants des sous modèles à supprimer
     * @param type         Le type de l'action
     */
    Remover (
        type_Model *model, QString propertyName,
        QList<type_SubModel> (type_Model::*remove)(QList<type_Id>),
        void (type_Model::*add)(QList<type_Id>, QList<type_SubModel>),
        QList<type_Id> ids, int type = GROUP_ACTION
    ) :
        GroupAction<type_Id>(ids, propertyName, type),
        _model(model),
        _remove(remove),
        _add(add)
    {}

    void execute ()
    {
        _values = (_model->*_remove)(GroupAction<type_Id>::selection());
    }

    void reverse ()
    {
        (_model->*_add)(GroupAction<type_Id>::selection(), _values);
    }

private:
    type_Model *_model;
    QList<type_SubModel> _values;
    QList<type_SubModel> (type_Model::*_remove)(QList<type_Id>);
    void (type_Model::*_add)(QList<type_Id>, QList<type_SubModel>);
};

#endif
