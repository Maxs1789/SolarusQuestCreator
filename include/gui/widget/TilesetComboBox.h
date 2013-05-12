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
#ifndef TILESET_COMBOBOX_H
#define TILESET_COMBOBOX_H

#include <QComboBox>
#include "view/QuestView.h"

/**
 * @brief ComboBox listant les tilesets d'une quete (Tileset).
 */
class TilesetComboBox : public QComboBox, public QuestView
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la comboBox des tilesets.
     *
     * @param quest La quete d'ou récupérer les tilesets
     */
    TilesetComboBox (Quest *quest);
    /**
     * @brief Destructeur de la comboBox.
     */
    ~TilesetComboBox ();

    void refreshResource (ResourceType type, QString id);
    void addResource (ResourceType type, QString id);
    void removeResource (ResourceType type, QString id);

private:
    Quest *_quest;
};

#endif
