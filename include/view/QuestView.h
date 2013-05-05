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
#ifndef QUEST_VIEW_H
#define QUEST_VIEW_H

#include <QString>
#include "sol/types.h"

/**
 * @brief Vue abstraite d'une quête (Quest).
 */
class QuestView
{
public:
    /**
     * @brief Appelée lorsqu'une ressource de la quête est mise à jour.
     *
     * @param type Le type de la ressource ajoutée
     * @param id   L'identifiant de la ressource ajoutée
     *
     * @see Quest
     */
    virtual void refreshResource (ResourceType type, QString id) = 0;
    /**
     * @brief Appelée lorsqu'une ressource est ajouté à la quête.
     *
     * @param type Le type de la ressource ajoutée
     * @param id   L'identifiant de la ressource ajoutée
     *
     * @see Quest
     */
    virtual void addResource (ResourceType type, QString id) = 0;
    /**
     * @brief Appelée lorsqu'une ressource est supprimée de la quête.
     *
     * @param type Le type de la ressource ajoutée
     * @param id   L'identifiant de la ressource ajoutée
     *
     * @see Quest
     */
    virtual void removeResource (ResourceType type, QString id) = 0;
};

#endif
