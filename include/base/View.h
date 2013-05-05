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
#ifndef VIEW_H
#define VIEW_H

#include <QString>

/**
 * @brief Classe abstraire de vue.
 *
 * Cette classe à pour but de servir de parent commun à toute vue géré par un
 * modèle (Model). Celles-ci devant au minimum offrir une méthode dont le
 * prototype est `void simpleRefresh (string)`.
 */
class View
{
public:
    /**
     * @brief Appelée lorsqu'une action est exécutée sur le modèle.
     *
     * @param propertyName Nom de la propriété touché par l'action.
     */
    virtual void simpleRefresh (QString message) = 0;
};

#endif
