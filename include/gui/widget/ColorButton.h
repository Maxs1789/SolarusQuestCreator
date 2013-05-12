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
#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include <QPushButton>
#include <QColorDialog>

/**
 * @brief Bouton de sélection de couleur.
 */
class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de bouton de sélection de couleur.
     *
     * @param color La couleur à donner au bouton
     */
    ColorButton (QColor color = Qt::white) :
        _color(color)
    {
        _refresh();
        connect(this, SIGNAL(clicked()), this, SLOT(_onClick()));
    }
    /**
     * @brief Donne la couleur du bouton.
     *
     * @return La couleur du bouton.
     */
    QColor color () const
    {
        return _color;
    }

public slots:
    /**
     * @brief change la couleur à donner au bouton.
     *
     * @param color La nouvelle couleur à donner au bouton
     */
    void setColor (QColor color)
    {
        if (color != _color) {
            _color = color;
            _refresh();
        }
    }

signals:
    /**
     * @brief Emit lorsque le bouton change de couleur.
     */
    void colorChange (QColor);

private:
    QColor _color;

    void _refresh ()
    {
        QString style = "QPushButton{border:1px solid gray;border-radius:3px;";
        style += "margin:5px;max-width:24px;max-height:16px;background-color:";
        style += _color.name() + "}";
        setStyleSheet(style);
    }

private slots:
    void _onClick ()
    {
        QColor color = QColorDialog::getColor(_color, (QWidget*)parent());
        if (color.isValid() && color != _color) {
            _color = color;
            _refresh();
            emit colorChange(color);
        }
    }
};

#endif
