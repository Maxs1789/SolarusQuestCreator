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
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "sol/Quest.h"
#include "view/QuestView.h"
#include "sol/Resource.h"
#include "sol/Tileset.h"
#include "sol/Sprite.h"
#include "sol/TilePattern.h"
#include "util/FileTools.h"

Quest *Quest::load (QString directory) throw(QuestException)
{
    directory = FileTools::absolutePath(directory);
    Quest *quest = new Quest(directory);
    try {
        quest->_loadProjectDB();
        quest->_loadQuestDat();
    } catch (const IOException &ex) {
        throw QuestException(
            QObject::tr("cannot load the quest, ") + ex.message()
        );
    }
    return quest;
}

void Quest::save () throw (SQCException)
{
    _saveQuestDat();
    _saveProjectDB();
}

Quest::~Quest ()
{
    for (int type = MAP; type < N_RESOURCE_TYPE; ++type) {
        QMap<QString, Resource *>::Iterator it = _resources[type].begin();
        for (; it != _resources[type].end(); ++it) {
            delete it.value();
        }
    }
}

QString Quest::directory () const
{
    return _directory;
}

QString Quest::dataDirectory () const
{
    return _dataDirectory;
}

QString Quest::writeDir () const
{
    return _writeDir;
}

QString Quest::titleBar () const
{
    return _titleBar;
}

Quest::Quest (QString directory) throw(QuestException) :
    _directory(directory),
    _dataDirectory(directory + "data/")
{}

bool Quest::resourceExists (ResourceType type, QString id) const
{
    return _resourceNames[type].contains(id);
}

bool Quest::tilesetExists (QString id) const
{
    return resourceExists(TILESET, id);
}

bool Quest::spriteExists (QString id) const
{
    return resourceExists(SPRITE, id);
}

Tileset Quest::tileset (QString id) throw(QuestException)
{
    if (!_resources[TILESET].contains(id)) {
        if (_resourceNames[TILESET].contains(id)) {
            _resources[TILESET][id] = Tileset::load(
                _dataDirectory, id, _resourceNames[TILESET][id]
            );
        } else {
            QString msg = QObject::tr("tileset $1 does not exists");
            msg.replace("$1", id);
            throw QuestException(msg);
        }
    }
    return ((Tileset*)_resources[TILESET][id])->copy();
}

Sprite Quest::sprite (QString id) throw(QuestException)
{
    if (!_resources[SPRITE].contains(id)) {
        if (_resourceNames[SPRITE].contains(id)) {
            _resources[SPRITE][id] = Sprite::load(
                _dataDirectory, id, _resourceNames[SPRITE][id]
            );
        } else {
            QString msg = QObject::tr("sprite $1 does not exists");
            msg.replace("$1", id);
            throw QuestException(msg);
        }
    }
    return ((Sprite*)_resources[SPRITE][id])->copy();
}

QMap<QString, QString> Quest::resourceNames (ResourceType type) const
{
    return _resourceNames[type];
}

QString Quest::resourceName (ResourceType type, QString id) const
{
    if (!_resourceNames[type].contains(id)) {
        return "";
    }
    return _resourceNames[type][id];
}

QList<QString> Quest::resourceIds (ResourceType type) const
{
    return _resourceNames[type].keys();
}

QList<QString> Quest::tilesetIds () const
{
    return resourceIds(TILESET);
}

QList<QString> Quest::spriteIds () const
{
    return resourceIds(SPRITE);
}

void Quest::setTileset (QString id, const Tileset &tileset)
{
    Tileset *resource = new Tileset(id);
    *resource = tileset;
    _setResource(TILESET, id, resource);
}

void Quest::setSprite (QString id, const Sprite &sprite)
{
    Sprite *resource = new Sprite(id);
    *resource = sprite;
    _setResource(SPRITE, id, resource);
}

bool Quest::removeResource (ResourceType type, QString id)
{
    if (!_resourceNames[type].contains(id)) {
        return false;
    }
    delete _resources[type][id];
    _resources[type].remove(id);
    _resourceNames[type].remove(id);
    for (int i = 0; i < _views.size(); ++i) {
        _views[i]->removeResource(type, id);
    }
    return true;
}

bool Quest::removeTileset(QString id)
{
    return removeResource(TILESET, id);
}

bool Quest::removeSprite (QString id)
{
    return removeResource(SPRITE, id);
}

void Quest::attach (QuestView *view)
{
    if (!_views.contains(view)) {
        _views.push_back(view);
    }
}

void Quest::detach (QuestView *view)
{
    int i = _views.indexOf(view);
    if (i >= 0) {
        _views.removeAt(i);
    }
}

void Quest::_loadQuestDat () throw(QuestException)
{
    lua_State *L = luaL_newstate();
    lua_register(L, "quest", _lua_quest);
    lua_pushlightuserdata(L, this);
    lua_setfield(L, LUA_REGISTRYINDEX, "quest");
    QString filename = _dataDirectory + "quest.dat";
    if (luaL_loadfile(L, filename.toStdString().c_str())) {
        throw QuestException(QObject::tr("lua load error"));
    }
    if (lua_pcall(L, 0, 0, 0) != 0) {
        throw QuestException(QObject::tr("lua call error"));
    }
    lua_close(L);
}

void Quest::_loadProjectDB () throw(IOException)
{
    QString filename = _dataDirectory + "project_db.dat";
    if (!FileTools::fileExists(filename)) {
        throw IOException(IOException::FILE_N_EXISTS, "data/project_db.dat");
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IOException(IOException::FILE_N_READ, "data/project_db.dat");
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line != "") {
            QStringList list = line.split("\t");
            if (list.length() == 3) {
                ResourceType type = (ResourceType)list[0].toInt();
                _resourceNames[type][list[1]] = list[2];
            }
        }
    }
    file.close();
}

void Quest::_saveQuestDat () throw(IOException)
{
    QString filename = _dataDirectory + "quest.dat";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw IOException(IOException::FILE_N_WRITE, "quest.dat");
    }
    file.write("quest{\n");
    file.write("  write_dir = \"");
    file.write(_writeDir.toLocal8Bit());
    file.write("\",\n  title_bar = \"");
    file.write(_titleBar.toLocal8Bit());
    file.write("\"\n}");
    file.close();
}

void Quest::_saveProjectDB () throw(IOException)
{
    QString filename = _dataDirectory + "project_db.dat";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw IOException(IOException::FILE_N_WRITE, "project_db.dat");
    }
    QTextStream out(&file);
    for (int type = MAP; type < N_RESOURCE_TYPE; type++) {
        QMap<QString, QString>::iterator it = _resourceNames[type].begin();
        for (; it != _resourceNames[type].end(); it++) {
            out << type << "\t" << it.key() << "\t" << it.value() << "\n";
        }
    }
    file.close();
}

void Quest::_setResource (ResourceType type, QString id, Resource *resource)
{
    bool exists = _resourceNames[type].contains(id);
    _resources[type][id] = resource;
    _resourceNames[type][id] = resource->name();
    for (int i = 0; i < _views.size(); ++i) {
        if (exists) {
            _views[i]->refreshResource(type, id);
        } else {
            _views[i]->addResource(type, id);
        }
    }
}

int Quest::_lua_quest (lua_State *L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "quest");
    Quest* quest = (Quest*)lua_touserdata(L, -1);
    lua_pop(L, 1);

    lua_settop(L, 1);
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        QString key = luaL_checkstring(L, 2);
        if (key == "write_dir") {
            quest->_writeDir = luaL_checkstring(L, 3);
        } else if (key == "title_bar") {
            quest->_titleBar = luaL_checkstring(L, 3);
        }
        lua_pop(L, 1);
    }
    return 0;
}
