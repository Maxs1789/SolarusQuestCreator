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
#include <QSettings>
#include "gui/graphics/SpriteDirectionGraphicsView.h"

SpriteDirectionGraphicsView::SpriteDirectionGraphicsView () :
    _originX(0),
    _originY(0)
{
    QSettings s;
    s.beginGroup("sprite_direction_graphics_view");
    _selectionColor = QColor(s.value("origin_color", "#fff").toString());
    setZoom(s.value("zoom", 2.0).toFloat());
    setBackgroundBrush(
        QColor(s.value("background_color", "#c0c0c0").toString())
    );
    _showOrigin = s.value("show_origin", true).toBool();
    _cross = s.value("origin_mode", true).toBool();
    s.endGroup();
    setScene(new QGraphicsScene());
}

bool SpriteDirectionGraphicsView::showOrigin () const
{
    return _showOrigin;
}

bool SpriteDirectionGraphicsView::point () const
{
    return !_cross;
}

bool SpriteDirectionGraphicsView::cross () const
{
    return _cross;
}

void SpriteDirectionGraphicsView::setOrigin (int originX, int originY)
{
    if (originX != _originX || originY != _originY) {
        _originX = originX;
        _originY = originY;
        viewport()->update();
    }
}

void SpriteDirectionGraphicsView::saveSettings () const
{
    QSettings s;
    s.beginGroup("sprite_direction_graphics_view");
    s.setValue("origin_color", _selectionColor.name());
    s.setValue("zoom", zoom());
    s.setValue("background_color", backgroundBrush().color().name());
    s.setValue("show_origin", _showOrigin);
    s.setValue("origin_mode", _cross);
    s.endGroup();
}

void SpriteDirectionGraphicsView::showOrigin (bool show)
{
    if (show != _showOrigin) {
        _showOrigin = show;
        viewport()->update();
        emit showOriginChange(show, _cross);
    }
}

void SpriteDirectionGraphicsView::showOriginPoint (bool point)
{
    if (_showOrigin != true || _cross == point) {
        _showOrigin = true;
        _cross = !point;
        viewport()->update();
        emit showOriginChange(_showOrigin, _cross);
    }
}

void SpriteDirectionGraphicsView::showOriginCross (bool cross)
{
    if (_showOrigin != true || _cross != cross) {
        _showOrigin = true;
        _cross = cross;
        viewport()->update();
        emit showOriginChange(_showOrigin, _cross);
    }
}

void SpriteDirectionGraphicsView::paintEvent (QPaintEvent *event)
{
    SQCGraphicsView::paintEvent(event);
    if (!isEnabled()) {
        return;
    }
    QPainter painter(viewport());
    if (_showOrigin) {
        QPen pen(selectionColor());
        QPoint p = mapFromScene(_originX, _originY);
        if (_cross) {
            int w = viewport()->width(), h = viewport()->height();
            painter.setPen(pen);
            painter.drawLine(p.x(), 0, p.x(), h);
            painter.drawLine(0, p.y(), w, p.y());
        } else {
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawPoint(p);
        }
    }
}
