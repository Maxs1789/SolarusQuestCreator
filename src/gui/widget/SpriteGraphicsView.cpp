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
#include "gui/widget/SpriteGraphicsView.h"
#include "sol/SpriteSelection.h"
#include "sol/SpriteAnimation.h"

SpriteGraphicsView::SpriteGraphicsView ()
{
    setBackgroundBrush(Qt::lightGray);
    setShowSceneBorder(true);
    setScene(new QGraphicsScene());
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
        addToSelection((ComplexSelection){(Rect){
            direction.x(), direction.y(), direction.width(), direction.height()
        }, direction.nbFrames(), direction.nbColumns()});
    } else if (selection.isNewDirection()) {
        setNewSelection(selection.newDirection());
        keepSelection();
    }
    viewport()->update();
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
