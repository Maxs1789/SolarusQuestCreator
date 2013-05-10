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
#ifndef SQC_GRAPHICS_VIEW_H
#define SQC_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QApplication>
#include "sol/types.h"

class SQCGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    SQCGraphicsView ();

    void setMakeSelection (bool canMake);

public slots:
    void setSelectionColor (QColor color);

protected:
    struct ComplexSelection
    {
        Rect rect;
        int length;
        int cols;
    };

    void mouseMoveEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    void paintEvent (QPaintEvent *event);
    void wheelEvent (QWheelEvent *event);

    void clear ();

    void setNewSelection (Rect selection);
    void keepSelection ();
    void addToSelection (const ComplexSelection &selection);

    virtual bool clickOnItems (QList<QGraphicsItem *> items) {
        return false;
    }
    virtual void onSelection (const Rect &selection) {
        keepSelection();
    }

private:
    float _zoom, _zoomMin, _zoomMax;
    int _zoomFactor;
    bool _canMakeSelection;
    bool _inSelection;
    bool _keepSelection;
    Rect _selection;
    int _x1, _y1, _x2, _y2;
    int _gridW, _gridH;
    QList<ComplexSelection> _selections;
    QColor _selectionColor;

    void _computeSelection ();
    void _snapToGrid (int &x, int &y, const bool &ceil = false);
    void _drawNewSelection (QPainter *painter, const Rect &selection);
    void _drawComplexSelectionBorder (
        QPainter *painter, const ComplexSelection &selection
    );
    void _drawComplexSelectionShadow (
        QPainter *painter, const ComplexSelection &selection
    );
    QPolygonF _complexSelectionBorder(const ComplexSelection &selection);
    QList<QLineF> _complexSelectionVerticalLines(
        const ComplexSelection &selection
    );
    QList<QLineF> _complexSelectionHorizontalLines (
        const ComplexSelection &selection
    );
    void _getBorderShadows (
        const QPolygonF &polygon, QPolygonF &shadow1, QPolygonF &shadow2
    );
    QList<QLineF> _getVerticalLinesShadows(const QList<QLineF> &lines);
    QList<QLineF> _getHorizontalLinesShadows(const QList<QLineF> &lines);
};

#endif
