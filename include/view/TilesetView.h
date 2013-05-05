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
#ifndef TILESETVIEW_H
#define TILESETVIEW_H

#include "base/View.h"

/**
 * @brief Classe abstraite d'une vue d'un Tileset.
 */
class TilesetView : public View
{
public:
    /**
     * @brief Appelée lorsque la sélection du Tileset change.
     *
     * @param selection La nouvelle sélection du Tileset.
     */
    virtual void refreshSelection (QList<int> selection) = 0;
    /**
     * @brief Appelée lorsqu'un patron de tile a changé.
     *
     * @param id L'identifiant du patron de tile.
     */
    virtual void refreshPattern (int id) = 0;
    /**
     * @brief Appelée lorsque des patrons de tile ont été ajouté.
     *
     * @param selection La liste des identifiants des nouveaux patron de tile.
     */
    virtual void addPatterns (QList<int> selection) = 0;
    /**
     * @brief Appelée lorsque des patrons de tile ont été supprimé.
     *
     * @param selection La liste des identifiants de patron de tile supprimé.
     */
    virtual void removePatterns (QList<int> selection) = 0;
};

#endif
