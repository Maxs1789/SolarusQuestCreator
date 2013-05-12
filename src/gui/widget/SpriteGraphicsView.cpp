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
#include <QGraphicsPixmapItem>
#include <QSettings>
#include "gui/widget/SpriteGraphicsView.h"
#include "sol/SpriteSelection.h"
#include "sol/SpriteAnimation.h"

SpriteGraphicsView::SpriteGraphicsView (QStatusBar *statusBar) :
    SQCGraphicsView(statusBar)
{
    QSettings s;
    s.beginGroup("sprite_graphics_view");
    _showSceneBorder = s.value("show_scene_border", true).toBool();
    setBackgroundBrush(
        QColor(s.value("background_color", "#c0c0c0").toString())
    );
    setZoom(s.value("zoom", 1.0).toFloat());
    _snap = s.value("snap_to_grid", true).toBool();
    _gridW = s.value("grid_width", 16).toInt();
    _gridH = s.value("grid_height", 16).toInt();
    _selectionColor = QColor(s.value("selection_color", "#00f").toString());
    _displaySelectionShadow = s.value(
        "display_selection_shadow", true
    ).toBool();
    _showGrid = s.value("show_grid", false).toBool();
    _gridColor = QColor(s.value("grid_color", "#888").toString());
    _gridOpacity = s.value("grid_opacity", 0.5).toFloat();
    s.endGroup();
    setScene(new QGraphicsScene());
    setMouseTracking(true);
    _image = new QGraphicsPixmapItem;
    scene()->addItem(_image);
}

void SpriteGraphicsView::setImage (const QPixmap &image)
{
    _image->setPixmap(image);
    scene()->setSceneRect(image.rect());
}

void SpriteGraphicsView::setSelection (
    const SpriteAnimation &animation, const SpriteSelection &selection
) {
    clear();
    if (selection.haveDirection()) {
        int dir = selection.direction();
        SpriteDirection direction = animation.direction(dir);
        int x = direction.x(), y = direction.y();
        int w = direction.width(), h = direction.height();
        int nf = direction.nbFrames(), nc = direction.nbColumns();
        addToSelection((ComplexSelection){(Rect){x, y, w, h}, nf, nc});
        if (nf < nc) {
            nc = nf;
        }
        int nr = nf / nc;
        ensureVisible(x, y, w * nc, h * nr);
    } else if (selection.isNewDirection()) {
        setNewSelection(selection.newDirection());
        keepSelection();
    }
    viewport()->update();
}

void SpriteGraphicsView::saveSettings () const
{
    QSettings s;
    s.beginGroup("sprite_graphics_view");
    s.setValue("show_scene_border", _showSceneBorder);
    s.setValue("background_color", backgroundBrush().color().name());
    s.setValue("zoom", zoom());
    s.setValue("snap_to_grid", _snap);
    s.setValue("grid_width", _gridW);
    s.setValue("grid_height", _gridH);
    s.setValue("selection_color", _selectionColor.name());
    s.setValue("display_selection_shadow", _displaySelectionShadow);
    s.setValue("show_grid", _showGrid);
    s.setValue("grid_color", _gridColor.name());
    s.setValue("grid_opacity", _gridOpacity);
    s.endGroup();
}

void SpriteGraphicsView::onSelection (const Rect &selection)
{
    if (
        selection.x + selection.width > _image->pixmap().width() ||
        selection.y + selection.height > _image->pixmap().height()
    ) {
        emit newSelection((Rect){-1, -1, -1, -1});
    }
    emit newSelection(selection);
}
