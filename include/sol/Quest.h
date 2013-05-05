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
#ifndef QUEST_H
#define QUEST_H

#include "exception/QuestException.h"
#include "exception/IOException.h"
#include "Tileset.h"

class QuestView;

/**
 * @brief Quête de jeu.
 */
class Quest
{
public:
    static Quest *load (QString directory) throw(QuestException);

    void save () throw (SQCException);
    //void save (QString directory = "") throw(IOException);

    ~Quest ();

    QString directory () const;
    QString dataDirectory () const;
    QString writeDir () const;
    QString titleBar () const;

    bool resourceExists (ResourceType type, QString id) const;
    bool tilesetExists (QString id) const;
    bool spriteExists (QString id) const;

    Tileset tileset (QString id) throw(QuestException);
    Sprite sprite (QString id) throw(QuestException);

    QMap<QString, QString> resourceNames (ResourceType type) const;
    QString resourceName (ResourceType type, QString id) const;

    QList<QString> resourceIds (ResourceType type) const;
    QList<QString> tilesetIds () const;
    QList<QString> spriteIds () const;

    void setTileset (QString id, const Tileset &tileset);
    void setSprite (QString id, const Sprite &sprite);

    bool removeResource (ResourceType type, QString id);
    bool removeTileset (QString id);
    bool removeSprite (QString id);

    void attach (QuestView *view);
    void detach (QuestView *view);

private:
    QString _directory;
    QString _dataDirectory;
    QString _writeDir;
    QString _titleBar;
    QMap<QString, Resource *> _resources[N_RESOURCE_TYPE];
    QMap<QString, QString> _resourceNames[N_RESOURCE_TYPE];
    QList<QuestView *> _views;

    Quest (QString directory) throw(QuestException);

    void _loadQuestDat () throw(QuestException);
    void _loadProjectDB () throw(IOException);
    void _saveQuestDat () throw(IOException);
    void _saveProjectDB () throw(IOException);

    void _setResource (ResourceType type, QString id, Resource *resource);

    static int _lua_quest (lua_State *L);
};

#endif
