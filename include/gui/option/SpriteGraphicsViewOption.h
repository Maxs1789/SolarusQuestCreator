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
#ifndef SPRITE_GRAPHICS_VIEW_OPTION_H
#define SPRITE_GRAPHICS_VIEW_OPTION_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QGroupBox;
class QSpinBox;
class SpriteGraphicsView;
class ColorButton;

class SpriteGraphicsViewOption : public QWidget
{
    Q_OBJECT
public:
    SpriteGraphicsViewOption (SpriteGraphicsView *view = 0);
    ~SpriteGraphicsViewOption ();

    void setSettings ();
    void save ();

private:
    SpriteGraphicsView *_view;
    bool _mustDelete;
    QCheckBox *_showSceneBorder;
    ColorButton *_backColor;
    QComboBox *_zoom;
    QGroupBox *_gridStyleGroup;
    QGroupBox *_gridSnapGroup;
    ColorButton *_gridColor;
    QSpinBox *_gridOpacity;
    QSpinBox *_gridWidth;
    QSpinBox *_gridHeight;
    QCheckBox *_displaySelectionShadow;
    ColorButton *_selectionColor;

    void _initWidgets ();
    void _refreshWidgets (const SpriteGraphicsView *view);
};

#endif
