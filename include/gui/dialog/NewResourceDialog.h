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
#ifndef NEW_RESOURCE_DIALOG_H
#define NEW_RESOURCE_DIALOG_H

#include <QDialog>
#include "sol/types.h"

class QLineEdit;
class QDialogButtonBox;

class NewResourceDialog : public QDialog
{
    Q_OBJECT
public:
    NewResourceDialog (QWidget *parent);

    QString name () const;
    QString id () const;

    void setResourceIds (QList<QString> resourceIds);

private:
    QLineEdit *_name;
    QLineEdit *_id;
    QDialogButtonBox *_buttonBox;
    QList<QString> _ids;
    bool _clean;

    void _initWidgets ();

private slots:
    void _nameChange (QString name);
    void _idChange (QString id);
};

#endif
