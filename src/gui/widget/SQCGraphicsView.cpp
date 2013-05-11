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
    _gridH(8),
    _selectionColor(Qt::blue),
    _showSceneBorder(false),
    _snap(true),
    _showGrid(false)
{
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void SQCGraphicsView::setMakeSelection (bool canMake)
{
    _canMakeSelection = canMake;
}

bool SQCGraphicsView::canMakeSelection () const
{
    return _canMakeSelection;
}

float SQCGraphicsView::zoom () const
{
    return _zoom;
}

QColor SQCGraphicsView::selectionColor () const
{
    return _selectionColor;
}

bool SQCGraphicsView::showSceneBorder () const
{
    return _showSceneBorder;
}

bool SQCGraphicsView::showGrid () const
{
    return _showGrid;
}

bool SQCGraphicsView::snap () const
{
    return _snap;
}

int SQCGraphicsView::gridWidth () const
{
    return _gridW;
}

int SQCGraphicsView::gridHeight () const
{
    return _gridH;
}

void SQCGraphicsView::setZoom (float zoom)
{
    if (zoom != _zoom && zoom >= _zoomMin && zoom <= _zoomMax) {
        _zoom = zoom;
        QTransform tran;
        tran.scale(_zoom, _zoom);
        setTransform(tran);
        emit zoomChange(zoom);
    }
}

void SQCGraphicsView::setSelectionColor (QColor color)
{
    if (color != _selectionColor) {
        _selectionColor = color;
        viewport()->update();
    }
}

void SQCGraphicsView::setShowSceneBorder (bool show)
{
    if (show != _showSceneBorder) {
        _showSceneBorder = show;
        viewport()->update();
        emit showSceneBorderChange(show);
    }
}

void SQCGraphicsView::setShowGrid (bool show)
{
    if (show != _showGrid) {
        _showGrid = show;
        viewport()->update();
        emit showGridChange(show);
    }
}

void SQCGraphicsView::setSnap (bool snap)
{
    if (snap != _snap) {
        _snap = snap;
        emit snapChange(snap);
    }
}

void SQCGraphicsView::setGridWidth (int width)
{
    if (width < 1) {
        width = 1;
    }
    if (width != _gridW) {
        _gridW = width;
        viewport()->update();
        emit gridWidthChange(width);
    }
}

void SQCGraphicsView::setGridHeight (int height)
{
    if (height < 1) {
        height = 1;
    }
    if (height != _gridH) {
        _gridH = height;
        viewport()->update();
        emit gridHeightChange(height);
    }
}

void SQCGraphicsView::mousePressEvent (QMouseEvent *event)
{
    clear();
    if (!clickOnItems(items(event->pos())) && _canMakeSelection) {
        QPointF pos = mapToScene(event->pos());
        _x1 = _x2 = pos.x(); _y1 = _y2 = pos.y();
        if (_snap) {
            _snapToGrid(_x1, _y1);
            _snapToGrid(_x2, _y2, true);
        }
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
        if (_snap) {
            _snapToGrid(_x2, _y2);
            if (_x2 >= _x1) {
                _x2 += _gridW;
            }
            if (_y2 >= _y1) {
                _y2 += _gridH;
            }
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
    if (!isEnabled()) {
        return;
    }
    QPainter painter(viewport());
    if (_showSceneBorder) {
        QPolygonF polygon = mapFromScene(sceneRect());
        painter.drawRect(polygon.boundingRect().adjusted(-1, -1, 0, 0));
    }
    if (_showGrid) {
        painter.setPen(QColor(64, 64, 64, 128));
        int w = sceneRect().width(), h = sceneRect().height();
        for (int x = _gridW; x < w; x += _gridW) {
            painter.drawLine(mapFromScene(x, 0), mapFromScene(x, h));
        }
        for (int y = _gridH; y < h; y += _gridH) {
            painter.drawLine(mapFromScene(0, y), mapFromScene(w, y));
        }
    }
    if (_selections.size()) {
        QColor shadowColor = _selectionColor;
        shadowColor.setAlpha(85);
        painter.setPen(shadowColor);
        for (int i = 0; i < _selections.size(); i++) {
            _drawComplexSelectionShadow(&painter, _selections[i]);
        }
        painter.setPen(_selectionColor);
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
        emit zoomChange(_zoom);
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
    ComplexSelection complex = (ComplexSelection){(Rect){
        selection.x, selection.y, selection.width, selection.height
    }, 1, 1};
    painter->setPen(QColor(0, 0, 0, 85));
    _drawComplexSelectionShadow(painter, complex);
    painter->setPen(QColor(64, 64, 64));
    _drawComplexSelection(painter, complex);
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    _drawComplexSelection(painter, complex);
}

void SQCGraphicsView::_drawComplexSelection (
    QPainter *painter, const ComplexSelection &selection
) {
    QPolygonF borderPolygon = _complexSelectionBorder(selection);
    QList<QLineF> innerLines = _complexSelectionInnerLines(selection);
    painter->drawPolygon(borderPolygon);
    for (int i = 0; i < innerLines.size(); i++) {
        painter->drawLine(innerLines[i]);
    }
}

void SQCGraphicsView::_drawComplexSelectionShadow (
    QPainter *painter, const ComplexSelection &selection
) {
    QPolygonF borderPolygon = _complexSelectionBorder(selection);
    QPolygonF shadow = _getBorderShadow(borderPolygon);
    QList<QPolygonF> innerShadows = _complexSelectionInnerShadows(selection);
    painter->drawPolygon(shadow);
    for (int i = 0; i < innerShadows.size(); i++) {
        painter->drawPolygon(innerShadows[i]);
    }
}

QPolygonF SQCGraphicsView::_complexSelectionBorder (
    const ComplexSelection &selection
) {
    int x = selection.rect.x, y = selection.rect.y;
    int w = selection.rect.width, h = selection.rect.height;
    int l = selection.length, c = selection.cols;
    int r = (l / c);
    if (l < c || l % c == 0) {
        QPolygon polygon;
        if (l < c) {
            polygon = mapFromScene(x, y, w * l, h);
        } else {
            polygon = mapFromScene(x, y, w * c, h * r);
        }
        polygon = polygon.boundingRect().adjusted(0, 0, -2, -2);
        return polygon;
    }
    QPolygon polygon;
    int x2 = x + ((l % c) * w), x3 = x + (c * w);
    int y2 = y + (r * h), y3 = y2 + h;
    polygon << mapFromScene(x, y);
    QPoint p = mapFromScene(x3, y);
    p.setX(p.x() - 1);
    polygon << p;
    p = mapFromScene(x3, y2);
    p.setX(p.x() - 1); p.setY(p.y() - 1);
    polygon << p;
    p = mapFromScene(x2, y2);
    p.setX(p.x() - 1); p.setY(p.y() - 1);
    polygon << p;
    p = mapFromScene(x2, y3);
    p.setX(p.x() - 1); p.setY(p.y() - 1);
    polygon << p;
    p = mapFromScene(x, y3);
    p.setY(p.y() - 1);
    polygon << p;
    return polygon;
}

QList<QLineF> SQCGraphicsView::_complexSelectionInnerLines (
    const ComplexSelection &selection
) {
    QList<QLineF> lines;
    int l = selection.length;
    if (l <= 1) {
        return lines;
    }
    int c = selection.cols;
    int mc = l % c;
    int sx = selection.rect.x, sy = selection.rect.y;
    int sw = selection.rect.width, sh = selection.rect.height;
    int rr = l / c;
    int rh = sh * (rr + 1);
    int rc = l < c ? l : c;
    for (int i = 1; i < rc; i++) {
        int x = sx + (i * sw);
        int h = rh - (i >= mc ? sh : 0);
        QLineF line(mapFromScene(x, sy), mapFromScene(x, sy + h));
        QPointF p2 = line.p2(); p2.setY(p2.y() - 1);
        line.setP2(p2);
        line.translate(-1, 0);
        lines.push_back(line);
    }
    int w = sw * rc;
    for (int i = 1; i <= rr; i++) {
        int y = sy + (i * sh);
        QLineF line(mapFromScene(sx, y), mapFromScene(sx + w, y));
        QPointF p = line.p2(); p.setX(p.x() - 1);
        line.setP2(p);
        line.translate(0, -1);
        lines.push_back(line);
    }
    return lines;
}

QPolygonF SQCGraphicsView::_getBorderShadow (const QPolygonF &polygon)
{
    QPolygonF shadow;
    if (polygon.size() == 4) {
        shadow = polygon.boundingRect().adjusted(-1, -1, 1, 1);
    } else {
        QPointF p1 = polygon.at(0), p2 = polygon.at(2), p3 = polygon.at(4);
        int x1 = p1.x() - 1, x2 = p3.x() + 1, x3 = p2.x() + 1;
        int y1 = p1.y() - 1, y2 = p2.y() + 1, y3 = p3.y() + 1;
        shadow << QPointF(x1, y1);
        shadow << QPointF(x3, y1);
        shadow << QPointF(x3, y2);
        shadow << QPointF(x2, y2);
        shadow << QPointF(x2, y3);
        shadow << QPointF(x1, y3);
    }
    return shadow;
}

QList<QPolygonF> SQCGraphicsView::_complexSelectionInnerShadows (
    const ComplexSelection &selection
) {
    QList<QPolygonF> list;
    int l = selection.length, c = selection.cols;
    int sx = selection.rect.x, sy = selection.rect.y;
    int w = selection.rect.width, h = selection.rect.height;
    for (int i = 0; i < l; i++) {
        int x = (i % c) * w;
        int y = (int)(i / c) * h;
        QPolygon polygon = mapFromScene(sx + x, sy + y, w, h);
        QPointF p1 = polygon.at(0);
        if (x == 0) {
            p1.setX(p1.x() + 1);
        }
        if (y == 0) {
            p1.setY(p1.y() + 1);
        }
        QPointF p2 = polygon.at(2);
        p2.setX(p2.x() - 2);
        p2.setY(p2.y() - 2);
        list.push_back(QRectF(p1, p2));
    }
    return list;
}
