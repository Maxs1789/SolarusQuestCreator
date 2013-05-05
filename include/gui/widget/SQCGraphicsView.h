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
#include <QKeyEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QApplication>

#include <QDebug>

class SQCGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    SQCGraphicsView () {}

protected:

    void wheelEvent (QWheelEvent *event)
    {
        if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            int v = horizontalScrollBar()->value();
            horizontalScrollBar()->setValue(v - event->delta());
        } else if (
            QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)
        ) {
            QTransform tran;
            float zoom = transform().m11();
            if (event->delta() < 0) {
                if (zoom > 1) {
                    zoom /= 1.25;
                }
            } else if (zoom < 8) {
                zoom *= 1.25;
            }
            tran.scale(zoom, zoom);
            setTransform(tran);
        } else {
            QGraphicsView::wheelEvent(event);
        }
    }
};

#endif
