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

class QStatusBar;

class SQCGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    SQCGraphicsView (QStatusBar *statusBar = 0);

    void setMakeSelection (bool canMake);

    bool canMakeSelection () const;
    float zoom () const;
    QColor selectionColor () const;
    bool displaySelectionShadow () const;
    bool showSceneBorder () const;
    bool showGrid () const;
    QColor gridColor () const;
    float gridOpacity () const;
    bool snap () const;
    int gridWidth () const;
    int gridHeight () const;

public slots:
    void setZoom (float zoom);
    void setSelectionColor (QColor color);
    void setDisplaySelectionShadow (bool display);
    void setShowSceneBorder (bool show);
    void setShowGrid (bool show);
    void setGridColor (QColor color);
    void setGridOpacity (float opacity);
    void setSnap (bool snap);
    void setGridWidth (int width);
    void setGridHeight (int height);

signals:
    void zoomChange (float);
    void selectionColorChange (QColor);
    void displaySelectionShadowChange (bool);
    void showSceneBorderChange (bool);
    void showGridChange (bool);
    void gridColorChange (QColor);
    void gridOpacityChange (float);
    void snapChange (bool);
    void gridWidthChange (int);
    void gridHeightChange (int);

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
    virtual void paintEvent (QPaintEvent *event);
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

protected:
    int _gridW, _gridH;
    QColor _selectionColor;
    bool _displaySelectionShadow;
    bool _showSceneBorder;
    bool _showGrid;
    QColor _gridColor;
    float _gridOpacity;
    bool _snap;

private:
    float _zoom, _zoomMin, _zoomMax;
    int _zoomFactor;
    bool _canMakeSelection;
    bool _inSelection;
    bool _keepSelection;
    Rect _selection;
    int _x1, _y1, _x2, _y2;
    QList<ComplexSelection> _selections;
    int _mx, _my;
    QStatusBar *_statusBar;

    void _computeSelection ();
    void _snapToGrid (int &x, int &y, const bool &ceil = false);
    void _drawNewSelection (QPainter *painter, const Rect &selection);
    void _drawComplexSelection (
        QPainter *painter, const ComplexSelection &selection
    );
    void _drawComplexSelectionShadow (
        QPainter *painter, const ComplexSelection &selection
    );
    QPolygonF _complexSelectionBorder(const ComplexSelection &selection);
    QList<QLineF> _complexSelectionInnerLines (
        const ComplexSelection &selection
    );
    QPolygonF _getBorderShadow (const QPolygonF &polygon);
    QList<QPolygonF> _complexSelectionInnerShadows (
        const ComplexSelection &selection
    );

    void _refreshStatusBar ();
};

#endif
