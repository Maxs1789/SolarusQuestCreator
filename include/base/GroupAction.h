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
#ifndef GROUP_ACTION_H
#define GROUP_ACTION_H

#include <QList>
#include "Action.h"

/** Type d'action de groupe. */
#define GROUP_ACTION 1

/**
 * @brief Classe d'action de groupe.
 *
 * Cette classe est destinée à etre héritée par les classes d'action sur un
 * groupe de propriétées ou de sous-modèles.
 */
template<typename type_Id>
class GroupAction : public Action
{
public:
    /**
     * @brief Donne la sélection des propriétées ou sous-modèles modifié par
     *         l'action.
     *
     * @return La sélection des propriétées ou sous-modèles.
     */
    QList<type_Id> selection () const
    {
        return _selection;
    }

protected:
    /**
     * @brief Constructeur d'action de groupe.
     *
     * @param selection La sélection des propriétées ou sous-modèles.
     * @param message   Le message de l'action destiné aux vues.
     * @param type      Le type de l'action.
     */
    GroupAction (
        QList<type_Id> selection, QString message = "", int type = GROUP_ACTION
    ) :
        Action(message, type),
        _selection(selection)
    {}

private:
    QList<type_Id> _selection;
};

#endif
