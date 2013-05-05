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
#include <QObject>
#include "sol/TilePattern.h"

TilePattern::TilePattern (int id) :
    _id(id),
    _ground(TRAVERSABLE),
    _defaultLayer(LOW),
    _scrolling(NO_SCROLLING),
    _positions((Positions){0, 0, -1, -1, -1, -1, false}),
    _width(8),
    _height(8)
{}

TilePattern::TilePattern (int x, int y, int width, int height, int id)
    throw(SQCException) :
    _id(id),
    _ground(TRAVERSABLE),
    _defaultLayer(LOW),
    _scrolling(NO_SCROLLING),
    _positions((Positions){x, y, -1, -1, -1, -1, false}),
    _width(width),
    _height(height)
{
    _checkWidth(width);
    _checkHeight(height);
    _checkXY(x, y);
}

TilePattern::TilePattern (const TilePattern &other, int id) :
    _id(id),
    _ground(other._ground),
    _defaultLayer(other._defaultLayer),
    _scrolling(other._scrolling),
    _positions(other._positions),
    _width(other._width),
    _height(other._height)
{}

int TilePattern::id () const
{
    return _id;
}

Ground TilePattern::ground () const
{
    return _ground;
}

Layer TilePattern::defaultLayer () const
{
    return _defaultLayer;
}

Scrolling TilePattern::scrolling () const
{
    return _scrolling;
}

int TilePattern::width () const
{
    return _width;
}

int TilePattern::height () const
{
    return _height;
}

int TilePattern::x () const
{
    return _positions.x1;
}

int TilePattern::y () const
{
    return _positions.y1;
}

int TilePattern::x2 () const
{
    return _positions.x2;
}

int TilePattern::y2 () const
{
    return _positions.y2;
}

int TilePattern::x3 () const
{
    return _positions.x3;
}

int TilePattern::y3 () const
{
    return _positions.y3;
}

bool TilePattern::isSeq0121 () const
{
    return _positions.seq0121;
}

bool TilePattern::isAnimated () const
{
    return _positions.x2 >= 0;
}

void TilePattern::setGround (Ground ground)
{
    _ground = ground;
}

void TilePattern::setDefaultLayer (Layer defaultLayer)
{
    _defaultLayer = defaultLayer;
}

void TilePattern::setScrolling (Scrolling scrolling)
{
    _scrolling = scrolling;
}

void TilePattern::setWidth (int width) throw(SQCException)
{
    _checkWidth(width);
    _width = width;
}

void TilePattern::setHeight (int height) throw(SQCException)
{
    _checkHeight(height);
    _height = height;
}

void TilePattern::setPosition (int x, int y) throw(SQCException)
{
    _checkXY(x, y);
    _positions = (Positions){x, y, -1, -1, -1, -1, false};
}

void TilePattern::setPositions (
    int x1, int y1, int x2, int y2,
    int x3, int y3, bool seq0121
) throw(SQCException)
{
    _checkPositions(x1, y1, x2, y2, x3, y3);
    _positions = (Positions){x1, y1, x2, y2, x3, y3, seq0121};
}

QString TilePattern::toLua() const
{
    QString str = "tile_pattern {\n";
    str += "  id = " + QString::number(_id) + ",\n";
    str += "  ground = \"" + _groundToString(_ground) + "\",\n";
    str += "  default_layer = " + QString::number(_defaultLayer) + ",\n";
    Positions p = _positions;
    if (isAnimated()) {
        str += "  x = {" + QString::number(p.x1) +  ", ";
        str += QString::number(p.x2) + ", " + QString::number(p.x3);
        if (p.seq0121) {
            str += ", " + QString::number(p.x2);
        }
        str += "},\n  y = {" + QString::number(p.y1) +  ", ";
        str += QString::number(p.y2) + ", " + QString::number(p.y3);
        if (p.seq0121) {
            str += ", " + QString::number(p.y2);
        }
        str += "},\n";
    } else {
        str += "  x = " + QString::number(p.x1) + ",\n";
        str += "  y = " + QString::number(p.y1) + ",\n";
    }
    str += "  width = " + QString::number(_width) + ",\n";
    str += "  height = " + QString::number(_height);
    QString scrolling = _scrollingToString(_scrolling);
    if (scrolling != "") {
        str += ",\n  scrolling = \"" + scrolling + "\"";
    }
    return str + "\n}";
}

void TilePattern::_checkWidth (const int &width) const throw(SQCException)
{
    if (width <= 0 || width % 8 != 0) {
        throw SQCException(
            QObject::tr("width must be multiple of 8 and greater than 0")
        );
    }
}

void TilePattern::_checkHeight (const int &height) const throw(SQCException)
{
    if (height <= 0 || height % 8 != 0) {
        throw SQCException(
            QObject::tr("height must be multiple of 8 and greater than 0")
        );
    }
}

void TilePattern::_checkXY (const int &x, const int &y) const
    throw(SQCException)
{
    if (x < 0 || y < 0) {
        throw SQCException(
            QObject::tr("x and y must greater or equals than 0")
        );
    }
    if (x % 8 != 0 || y % 8 != 0) {
        throw SQCException(
            QObject::tr("x and y must be multiple than 8")
        );
    }
}

void TilePattern::_checkPositions (
    const int &x1, const int &y1, const int &x2,
    const int &y2, const int &x3, const int &y3
) const throw(SQCException)
{
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x3 < 0 || y3 < 0) {
        throw SQCException(
            QObject::tr("positions must be greater or equals than 0")
        );
    }
    if (
        x1 % 8 != 0 || y1 % 8 != 0 || x2 % 8 != 0 || y2 % 8 != 0 ||
        x3 % 8 != 0 || y3 % 8 != 0
    ) {
        throw SQCException(
            QObject::tr("positions must be multiple of 8")
        );
    }
}

QString TilePattern::_groundToString(Ground ground) const
{
    switch (ground) {
    case WALL: return "wall";
    case WALL_TOP_RIGHT: return "wall_top_right";
    case WALL_TOP_LEFT: return "wall_top_left";
    case WALL_BOTTOM_LEFT: return "wall_bottom_left";
    case WALL_BOTTOM_RIGHT: return "wall_bottom_right";
    case EMPTY: return "empty";
    case WATER_TOP_RIGHT: return "water_top_right";
    case WATER_TOP_LEFT: return "water_top_left";
    case WATER_BOTTOM_LEFT: return "water_bottom_left";
    case WATER_BOTTOM_RIGHT: return "water_bottom_right";
    case DEEP_WATER: return "deep_water";
    case SHALLOW_WATER: return "shallow_water";
    case HOLE: return "hole";
    case LADDER: return "ladder";
    case PRICKLES: return "prickles";
    case LAVA: return "lava";
    default: return "traversable";
    }
}

QString TilePattern::_scrollingToString(Scrolling scrolling) const
{
    switch (scrolling) {
    case SELF: return "self";
    case PARALLAX: return "parallax";
    default: return "";
    }
}
