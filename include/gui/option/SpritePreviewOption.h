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
#ifndef SPRITE_PREVIEW_OPTION_H
#define SPRITE_PREVIEW_OPTION_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QGroupBox;
class SpriteDirectionGraphicsView;
class ColorButton;

class SpritePreviewOption : public QWidget
{
    Q_OBJECT
public:
    SpritePreviewOption (SpriteDirectionGraphicsView *view = 0);
    ~SpritePreviewOption ();

    void setSettings ();
    void save ();

private:
    SpriteDirectionGraphicsView *_view;
    bool _mustDelete;
    ColorButton *_backColor;
    QComboBox *_zoom;
    QGroupBox *_originGroup;
    ColorButton *_originColor;
    QComboBox *_originMode;

    void _initWidgets ();
    void _refreshWidgets (const SpriteDirectionGraphicsView *view);
};

#endif
