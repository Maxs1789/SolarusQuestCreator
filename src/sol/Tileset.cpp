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
#include <QObject>
#include "sol/Tileset.h"
#include "sol/TilePattern.h"
#include "base/Setter.h"
#include "base/Adder.h"
#include "base/Remover.h"
#include "base/SubModelSetter.h"

#define NOTIFY_SELECTION 1
#define A_SET_PATTERN 12
#define A_ADD_PATTERN 13
#define A_REMOVE_PATTERN 14

const QString Tileset::p_backgroundColor = "background_color";
const QString Tileset::p_tilePattern = "tile_pattern";

Tileset *Tileset::load (QString dataDirectory, QString id, QString name)
    throw(SQCException)
{
    Tileset *tileset = new Tileset(id, name);
    lua_State *L = luaL_newstate();
    lua_register(L, "background_color", _lua_backgroundColor);
    lua_register(L, "tile_pattern", _lua_tilePattern);
    lua_pushlightuserdata(L, tileset);
    lua_setfield(L, LUA_REGISTRYINDEX, "tileset");
    QString filename = dataDirectory + tileset->filename();
    if (luaL_loadfile(L, filename.toStdString().c_str())) {
        throw SQCException(QObject::tr("lua load error"));
    }
    if (lua_pcall(L, 0, 0, 0) != 0) {
        throw SQCException(QObject::tr("lua call error"));
    }
    lua_close(L);
    return tileset;
}

Tileset::Tileset (QString id, QString name) :
    Resource(TILESET, id, name),
    _backgroundColor((Color){255, 255, 255}),
    _uniquePatternId(0)
{}

Tileset Tileset::copy () const
{
    Tileset tileset(id(), _name);
    tileset._backgroundColor = _backgroundColor;
    tileset._tilePatterns = _tilePatterns;
    tileset._uniquePatternId = _uniquePatternId;
    return tileset;
}

Color Tileset::backgroundColor () const
{
    return _backgroundColor;
}

bool Tileset::patternExists (int id) const
{
    return _tilePatterns.contains(id);
}

TilePattern Tileset::pattern (int id) const throw(SQCException)
{
    _checkPatternExists(id);
    return _tilePatterns[id];
}

QList<TilePattern> Tileset::patterns(QList<int> ids) const
{
    QList<TilePattern> list;
    for (int i = 0; i < ids.size(); i++) {
        if (_tilePatterns.contains(ids[i])) {
            list.push_back(_tilePatterns[ids[i]]);
        }
    }
    return list;
}

QList<int> Tileset::patternIds() const
{
    return _tilePatterns.keys();
}

QList<TilePattern> Tileset::allPatterns() const
{
    return _tilePatterns.values();
}

QList<TilePattern> Tileset::patternSelection () const
{
    return patterns(_selection);
}

bool Tileset::haveSelection () const
{
    return _selection.size();
}

QList<int> Tileset::selection() const
{
    return _selection;
}

QString Tileset::filename () const
{
    return QString("tilesets/") + id() + ".dat";
}

void Tileset::setName (QString name)
{
    if (name != _name) {
        doAction(new Setter<Tileset, QString>(
            this, Resource::p_name, &Tileset::_setName, name
        ));
    }
}

void Tileset::setBackgroundColor (Color color)
{
    if (color != _backgroundColor) {
        doAction(new Setter<Tileset, Color>(
            this, Tileset::p_backgroundColor,
            &Tileset::_setBackgroundColor, color
        ));
    }
}

int Tileset::addPattern (const TilePattern &pattern)
{
    int id = ++_uniquePatternId;
    QList<int> ids;
    QList<TilePattern> patterns;
    ids.push_back(id);
    patterns.push_back(pattern);
    doAction(new Adder<Tileset, TilePattern, int>(
        this, Tileset::p_tilePattern, &Tileset::_addPatterns,
        &Tileset::_removePatterns, ids, patterns, A_ADD_PATTERN
    ));
    return id;
}

QList<int> Tileset::addPatterns(QList<TilePattern> patterns)
{
    QList<int> ids;
    for (int i = 0; i < patterns.size(); i++) {
        ids.push_back(++_uniquePatternId);
    }
    doAction(new Adder<Tileset, TilePattern, int>(
        this, Tileset::p_tilePattern, &Tileset::_addPatterns,
        &Tileset::_removePatterns, ids, patterns, A_ADD_PATTERN
    ));
    return ids;
}

bool Tileset::removePattern (int id)
{
    if (patternExists(id)) {
        QList<int> ids;
        ids.push_back(id);
        doAction(new Remover<Tileset, TilePattern, int>(
            this, Tileset::p_tilePattern, &Tileset::_removePatterns,
            &Tileset::_addPatterns, ids, A_REMOVE_PATTERN
        ));
        return true;
    }
    return false;
}

void Tileset::removePatterns (QList<int> ids) throw(SQCException)
{
    for (int i = 0; i < ids.size(); i++) {
        _checkPatternExists(ids.at(i));
    }
    doAction(new Remover<Tileset, TilePattern, int>(
        this, Tileset::p_tilePattern, &Tileset::_removePatterns,
        &Tileset::_addPatterns, ids, A_REMOVE_PATTERN
    ));
}

bool Tileset::removeSelectionPatterns () throw(SQCException)
{
    removePatterns(_selection);
}

void Tileset::setPattern (int id, const TilePattern &pattern)
{
    if (_tilePatterns.contains(id)) {
        doAction(new SubModelSetter<Tileset, TilePattern, int>(
            this, Tileset::p_tilePattern, &Tileset::_setPattern,
            id, TilePattern(pattern, id), A_SET_PATTERN
        ));
    } else {
        QList<int> ids;
        QList<TilePattern> patterns;
        ids.push_back(id);
        patterns.push_back(TilePattern(pattern, id));
        doAction(new Adder<Tileset, TilePattern, int>(
            this, Tileset::p_tilePattern, &Tileset::_addPatterns,
            &Tileset::_removePatterns, ids, patterns, A_ADD_PATTERN
        ));
    }
}

void Tileset::selectPattern (int id)
{
    if (_tilePatterns.contains(id)) {
        _selection.push_back(id);
        userNotify(NOTIFY_SELECTION);
    }
}

void Tileset::unselectPattern (int id)
{
    if (_selection.contains(id)) {
        _selection.removeOne(id);
        userNotify(NOTIFY_SELECTION);
    }
}

void Tileset::onActionNotify (Action *action, TilesetView *view)
{
    int type = action->type();
    if (type == A_SET_PATTERN) {
        int id = ((SubModelSetter<Tileset, TilePattern, int>*)action)->id();
        view->refreshPattern(id);
    } else if (type == A_ADD_PATTERN || type == A_REMOVE_PATTERN) {
        QList<int> selection = ((GroupAction<int>*)action)->selection();
        if (type == A_ADD_PATTERN) {
            view->addPatterns(selection);
        } else {
            view->removePatterns(selection);
        }
    }
}

void Tileset::onUserNotify (int userType, TilesetView *view)
{
    if (userType == NOTIFY_SELECTION) {
        view->refreshSelection(_selection);
    }
}

QString Tileset::_setName (QString name)
{
    QString old = _name;
    _name = name;
    return old;
}

Color Tileset::_setBackgroundColor (Color color)
{
    Color old = _backgroundColor;
    _backgroundColor = color;
    return old;
}

TilePattern Tileset::_setPattern (int id, TilePattern pattern)
{
    TilePattern old = _tilePatterns[id];
    _tilePatterns[id] = pattern;
    _selection.clear();
    _selection.push_back(id);
    return old;
}

void Tileset::_addPatterns (QList<int> ids, QList<TilePattern> patterns)
{
    for (int i = 0; i < ids.size(); i++) {
        _tilePatterns[ids[i]] = patterns[i];
    }
    _selection = ids;
}

QList<TilePattern> Tileset::_removePatterns(QList<int> ids)
{
    QList<TilePattern> patterns;
    for (int i = 0; i < ids.size(); i++) {
        patterns.push_back(_tilePatterns[ids[i]]);
        _tilePatterns.remove(ids[i]);
    }
    return patterns;
}

void Tileset::_checkPatternExists (int id) const throw(SQCException)
{
    if (!_tilePatterns.contains(id)) {
        QString message = QObject::tr("tile_pattern $1 does not exists");
        message.replace("$1", QString::number(id));
        throw SQCException(message);
    }
}

int Tileset::_lua_backgroundColor (lua_State *L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "tileset");
    Tileset* tileset = (Tileset*)lua_touserdata(L, -1);
    lua_pop(L, 1);

    luaL_checktype(L, 1, LUA_TTABLE);
    lua_rawgeti(L, 1, 1);
    lua_rawgeti(L, 1, 2);
    lua_rawgeti(L, 1, 3);
    Color color = (Color){
        luaL_checkinteger(L, -3),
        luaL_checkinteger(L, -2),
        luaL_checkinteger(L, -1)
    };
    lua_pop(L, 3);

    tileset->_backgroundColor = color;
    return 0;
}

int Tileset::_lua_tilePattern (lua_State *L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "tileset");
    Tileset* tileset = (Tileset*)lua_touserdata(L, -1);
    lua_pop(L, 1);

    int id = -1, default_layer = -1, width = 0, height = 0;
    int x[] = { -1, -1, -1, -1 };
    int y[] = { -1, -1, -1, -1 };
    Ground ground = TRAVERSABLE;
    QString scrolling;
    int i = 0, j = 0;

    lua_settop(L, 1);
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        QString key = luaL_checkstring(L, 2);
        if (key == "id") {
            id = luaL_checkinteger(L, 3);
        } else if (key == "ground") {
            ground = _checkGround(L, 3);
        } else if (key == "default_layer") {
            default_layer = luaL_checkinteger(L, 3);
        } else if (key == "x") {
            if (lua_isnumber(L, 3)) {
                x[0] = luaL_checkinteger(L, 3);
                i = 1;
            } else {
                lua_pushnil(L);
                while (lua_next(L, 3) != 0 && i < 4) {
                    x[i] = luaL_checkinteger(L, 5);
                    ++i;
                    lua_pop(L, 1);
                }
            }
        } else if (key == "y") {
            if (lua_isnumber(L, 3)) {
            y[0] = luaL_checkinteger(L, 3);
            j = 1;
        } else {
            lua_pushnil(L);
            while (lua_next(L, 3) != 0 && j < 4) {
                y[j] = luaL_checkinteger(L, 5);
                ++j;
                lua_pop(L, 1);
            }
        }
        } else if (key == "width") {
            width = luaL_checkinteger(L, 3);
        } else if (key == "height") {
            height = luaL_checkinteger(L, 3);
        } else if (key == "scrolling") {
            scrolling = luaL_checkstring(L, 3);
        }
        lua_pop(L, 1);
    }

    if (id == -1) {
        luaL_argerror(L, 1, "Missing id for this tile pattern");
    }
    if (default_layer == -1) {
        luaL_argerror(L, 1, "Missing default layer for this tile pattern");
    }
    if (width == 0) {
        luaL_argerror(L, 1, "Missing width for this tile pattern");
    }
    if (height == 0) {
        luaL_argerror(L, 1, "Missing height for this tile pattern");
    }
    if (i != 1 && i != 3 && i != 4) {
        luaL_argerror(L, 1, "Invalid number of frames for x");
    }
    if (j != 1 && j != 3 && j != 4) {
        luaL_argerror(L, 1, "Invalid number of frames for y");
    }
    if (i != j) {
        luaL_argerror(L, 1, "The length of x and y must match");
    }

    TilePattern pattern(id);
    pattern.setGround(ground);
    pattern.setDefaultLayer((Layer)default_layer);
    pattern.setWidth(width);
    pattern.setHeight(height);
    if (scrolling == "self") {
        pattern.setScrolling(SELF);
    } else if (scrolling == "parallax") {
        pattern.setScrolling(PARALLAX);
    }
    if (i >= 3) {
        bool seq = i == 4;
        pattern.setPositions(x[0], y[0], x[1], y[1], x[2], y[2], seq);
    } else {
        pattern.setPosition(x[0], y[0]);
    }
    tileset->_tilePatterns[id] = pattern;
}

Ground Tileset::_checkGround (lua_State *L, int index)
{
    const QString name = luaL_checkstring(L, index);
    if (name == "wall") {
        return WALL;
    } else if (name == "wall_top_right") {
        return WALL_TOP_RIGHT;
    } else if (name == "wall_top_left") {
        return WALL_TOP_LEFT;
    } else if (name == "wall_bottom_left") {
        return WALL_BOTTOM_LEFT;
    } else if (name == "wall_bottom_right") {
        return WALL_BOTTOM_RIGHT;
    } else if (name == "wall_empty") {
        return EMPTY;
    } else if (name == "water_top_right") {
        return WATER_TOP_RIGHT;
    } else if (name == "water_top_left") {
        return WATER_TOP_LEFT;
    } else if (name == "water_bottom_left") {
        return WATER_BOTTOM_LEFT;
    } else if (name == "water_bottom_right") {
        return WATER_BOTTOM_RIGHT;
    } else if (name == "deep_water") {
        return DEEP_WATER;
    } else if (name == "shallow_water") {
        return SHALLOW_WATER;
    } else if (name == "hole") {
        return HOLE;
    } else if (name == "ladder") {
        return LADDER;
    } else if (name == "pickles") {
        return PRICKLES;
    } else if (name == "lava") {
        return LAVA;
    }
    return TRAVERSABLE;
}
