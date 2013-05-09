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
#include <QKeyEvent>
#include <QWheelEvent>
#include "gui/widget/SQCGraphicsView.h"

#include <QDebug>

SQCGraphicsView::SQCGraphicsView () :
    _zoom(1.0),
    _zoomMin(0.25),
    _zoomMax(8.0),
    _zoomFactor(2),
    _canMakeSelection(false),
    _inSelection(false),
    _keepSelection(false),
    _selection((Rect){-1, -1, -1, -1}),
    _gridW(8),
    _gridH(8)
{
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void SQCGraphicsView::setMakeSelection (bool canMake)
{
    _canMakeSelection = canMake;
}

void SQCGraphicsView::mousePressEvent (QMouseEvent *event)
{
    clear();
    if (!clickOnItems(items(event->pos())) && _canMakeSelection) {
        QPointF pos = mapToScene(event->pos());
        _x1 = _x2 = pos.x(); _y1 = _y2 = pos.y();
        _snapToGrid(_x1, _y1);
        _snapToGrid(_x2, _y2, true);
        _computeSelection();
        _inSelection = true;
        viewport()->repaint();
    }
}

void SQCGraphicsView::mouseMoveEvent (QMouseEvent *event)
{
    if (_inSelection) {
        QPointF pos = mapToScene(event->pos());
        _x2 = pos.x(); _y2 = pos.y();
        _snapToGrid(_x2, _y2);
        if (_x2 >= _x1) {
            _x2 += _gridW;
        }
        if (_y2 >= _y1) {
            _y2 += _gridH;
        }
        _computeSelection();
        viewport()->repaint();
    }
}

void SQCGraphicsView::mouseReleaseEvent (QMouseEvent *event)
{
    if (_inSelection) {
        _inSelection = false;
        onSelection(_selection);
        viewport()->repaint();
    }
}

void SQCGraphicsView::paintEvent (QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());
    if (_selections.size()) {
        for (int i = 0; i < _selections.size(); i++) {
            _drawComplexSelection(&painter, _selections[i]);
        }
    } else if (_inSelection || _keepSelection) {
        _drawNewSelection(&painter, _selection);
    }
}

void SQCGraphicsView::wheelEvent (QWheelEvent *event)
{
    if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
        int v = horizontalScrollBar()->value();
        horizontalScrollBar()->setValue(v - event->delta());
    } else if (
        QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)
    ) {
        if (event->delta() < 0) {
            if (_zoom > _zoomMin) {
                _zoom /= _zoomFactor;
            }
        } else if (_zoom < _zoomMax) {
            _zoom *= _zoomFactor;
        }
        QTransform tran;
        tran.scale(_zoom, _zoom);
        setTransform(tran);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void SQCGraphicsView::clear ()
{
    _selection = (Rect){-1, -1, -1, -1};
    _keepSelection = false;
    _selections.clear();
}

void SQCGraphicsView::setNewSelection (Rect selection)
{
    _selection = selection;
}

void SQCGraphicsView::keepSelection ()
{
    _keepSelection = true;
}

void SQCGraphicsView::addToSelection (const ComplexSelection &selection)
{
    _selections.push_back(selection);
}

void SQCGraphicsView::_computeSelection ()
{
    if (_x1 < _x2) {
        _selection.x = _x1;
        _selection.width = _x2 - _x1;
    } else {
        _selection.x = _x2;
        _selection.width = _x1 - _x2;
    }
    if (_y1 < _y2) {
        _selection.y = _y1;
        _selection.height = _y2 - _y1;
    } else {
        _selection.y = _y2;
        _selection.height = _y1 - _y2;
    }
}

void SQCGraphicsView::_snapToGrid (int &x, int &y, const bool &ceil)
{
    x -= x % _gridW;
    y -= y % _gridH;
    if (ceil) {
        x += _gridW;
        y += _gridH;
    }
}

void SQCGraphicsView::_drawNewSelection (
    QPainter *painter, const Rect &selection
) {
    QRect rect = mapFromScene(
        selection.x, selection.y, selection.width, selection.height
    ).boundingRect();
    int x = rect.x(), y = rect.y(), w = rect.width(), h = rect.height();
    painter->setPen(QColor(0, 0, 0, 128));
    painter->drawRect(x - 1, y - 1, w + 2, h + 2);
    painter->drawRect(x + 1, y + 1, w - 2, h - 2);
    painter->setPen(Qt::white);
    painter->drawRect(x, y, w, h);
}

void SQCGraphicsView::_drawComplexSelection (
    QPainter *painter, const ComplexSelection &selection
) {
    QPolygonF borderPolygon = _complexSelectionBorder(selection);
    QPolygonF shadow1, shadow2;
    _getBorderShadows(borderPolygon, shadow1, shadow2);
    QList<QLineF> verticalLines = _complexSelectionVerticalLines(selection);
    QList<QLineF> horizontalLines = _complexSelectionHorizontalLines(selection);
    QList<QLineF> verticalShadows = _getVerticalLinesShadows(verticalLines);
    QList<QLineF> horizontalShadows;
    horizontalShadows = _getHorizontalLinesShadows(horizontalLines);
    painter->setPen(QColor(0, 0, 0, 128));
    painter->drawPolygon(shadow1);
    painter->drawPolygon(shadow2);
    for (int i = 0; i < verticalShadows.size(); i++) {
        painter->drawLine(verticalShadows[i]);
    }
    for (int i = 0; i < horizontalShadows.size(); i++) {
        painter->drawLine(horizontalShadows[i]);
    }
    painter->setPen(Qt::black);
    painter->drawPolygon(borderPolygon);
    for (int i = 0; i < verticalLines.size(); i++) {
        painter->drawLine(verticalLines[i]);
    }
    for (int i = 0; i < horizontalLines.size(); i++) {
        painter->drawLine(horizontalLines[i]);
    }
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawPolygon(borderPolygon);
    for (int i = 0; i < verticalLines.size(); i++) {
        painter->drawLine(verticalLines[i]);
    }
    for (int i = 0; i < horizontalLines.size(); i++) {
        painter->drawLine(horizontalLines[i]);
    }
}

QPolygonF SQCGraphicsView::_complexSelectionBorder (
    const ComplexSelection &selection
) {
    int x = selection.rect.x, y = selection.rect.y;
    int w = selection.rect.width, h = selection.rect.height;
    int l = selection.length, c = selection.cols;
    if (l < c) {
        return mapFromScene(QPolygon(QRect(x, y, w * l, h)));
    }
    int r = (l / c);
    if (l % c == 0) {
        return mapFromScene(QPolygon(QRect(x, y, w * c, h * r)));
    }
    QPolygon polygon;
    int x2 = x + ((l % c) * w), x3 = x + (c * w);
    int y2 = y + (r * h), y3 = y2 + h;
    polygon << QPoint(x, y);
    polygon << QPoint(x3, y);
    polygon << QPoint(x3, y2);
    polygon << QPoint(x2, y2);
    polygon << QPoint(x2, y3);
    polygon << QPoint(x, y3);
    return mapFromScene(polygon);
}

QList<QLineF> SQCGraphicsView::_complexSelectionVerticalLines(
    const ComplexSelection &selection
) {
    QList<QLineF> lines;
    int c = selection.cols;
    if (c <= 1) {
        return lines;
    }
    int mc = selection.length % c;
    int sx = selection.rect.x, sy = selection.rect.y;
    int sh = selection.rect.height;
    sh *= (int)(selection.length / c) + 1;
    if (selection.length < c) {
        c = selection.length;
    }
    for (int i = 1; i < c; i++) {
        int x = sx + (i * selection.rect.width);
        int h = sh - (i >= mc ? selection.rect.height : 0);
        lines.push_back(QLineF(mapFromScene(x, sy), mapFromScene(x, sy + h)));
    }
    return lines;
}

QList<QLineF> SQCGraphicsView::_complexSelectionHorizontalLines(
    const ComplexSelection &selection
) {
    QList<QLineF> lines;
    int l = selection.length, c = selection.cols;
    if (l <= c) {
        return lines;
    }
    int sx = selection.rect.x, sy = selection.rect.y;
    int w = selection.rect.width, h = selection.rect.height;
    for (int i = c; i < l; i++) {
        int x = sx + ((i % c) * w);
        int y = sy + ((int)(i / c) * h);
        lines.push_back(QLineF(mapFromScene(x, y), mapFromScene(x + w, y)));
    }
    return lines;
}

void SQCGraphicsView::_getBorderShadows (
    const QPolygonF &polygon, QPolygonF &shadow1, QPolygonF &shadow2
) {
    QPointF p = polygon.at(0);
    shadow1 << QPointF(p.x() - 1, p.y() - 1);
    shadow2 << QPointF(p.x() + 1, p.y() + 1);
    p = polygon.at(1);
    shadow1 << QPointF(p.x() + 1, p.y() - 1);
    shadow2 << QPointF(p.x() - 1, p.y() + 1);
    p = polygon.at(2);
    shadow1 << QPointF(p.x() + 1, p.y() + 1);
    shadow2 << QPointF(p.x() - 1, p.y() - 1);
    if (polygon.size() == 4) {
        p = polygon.at(3);
        shadow1 << QPointF(p.x() - 1, p.y() + 1);
        shadow2 << QPointF(p.x() + 1, p.y() - 1);
    } else {
        p = polygon.at(3);
        shadow1 << QPointF(p.x() + 1, p.y() + 1);
        shadow2 << QPointF(p.x() - 1, p.y() - 1);
        p = polygon.at(4);
        shadow1 << QPointF(p.x() + 1, p.y() + 1);
        shadow2 << QPointF(p.x() - 1, p.y() - 1);
        p = polygon.at(5);
        shadow1 << QPointF(p.x() - 1, p.y() + 1);
        shadow2 << QPointF(p.x() + 1, p.y() - 1);
    }
}

QList<QLineF> SQCGraphicsView::_getVerticalLinesShadows (
    const QList<QLineF> &lines)
{
    QList<QLineF> shadows;
    for (int i = 0; i < lines.size(); i++) {
        QPointF p1 = lines[i].p1(), p2 = lines[i].p2();
        p1.setY(p1.y() + 2); p2.setY(p2.y() - 2);
        p1.setX(p1.x() - 1); p2.setX(p2.x() - 1);
        shadows.push_back(QLineF(p1, p2));
        p1.setX(p1.x() + 2); p2.setX(p2.x() + 2);
        shadows.push_back(QLineF(p1, p2));
    }
    return shadows;
}

QList<QLineF> SQCGraphicsView::_getHorizontalLinesShadows (
    const QList<QLineF> &lines
) {
    QList<QLineF> shadows;
    for (int i = 0; i < lines.size(); i++) {
        QPointF p1 = lines[i].p1(), p2 = lines[i].p2();
        p1.setX(p1.x() + 2); p2.setX(p2.x() - 2);
        p1.setY(p1.y() - 1); p2.setY(p2.y() - 1);
        shadows.push_back(QLineF(p1, p2));
        p1.setY(p1.y() + 2); p2.setY(p2.y() + 2);
        shadows.push_back(QLineF(p1, p2));
    }
    return shadows;
}
