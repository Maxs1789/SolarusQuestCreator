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
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "gui/dialog/NewResourceDialog.h"

NewResourceDialog::NewResourceDialog (QWidget *parent) :
    QDialog(parent),
    _clean(true)
{
    setWindowTitle(tr("New resource"));
    setModal(true);
    _initWidgets();
    connect(_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(
        _name, SIGNAL(textEdited(QString)), this, SLOT(_nameChange(QString))
    );
    connect(_id, SIGNAL(textEdited(QString)), this, SLOT(_idChange(QString)));
}

QString NewResourceDialog::name () const
{
    return _name->text();
}

QString NewResourceDialog::id () const
{
    return _id->text();
}

void NewResourceDialog::setResourceIds (QList<QString> resourceIds)
{
    _ids = resourceIds;
}

void NewResourceDialog::_initWidgets ()
{
    _name = new QLineEdit;
    _id = new QLineEdit;
    _buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );

    _buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), _name);
    formLayout->addRow(tr("Id:"), _id);
    formLayout->setLabelAlignment(Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(_buttonBox);
    setLayout(layout);
}

void NewResourceDialog::_nameChange (QString name)
{
    if (_clean) {
        name = name.toLower();
        name.replace(" ", "_");
        _id->setText(name);
    }
}

void NewResourceDialog::_idChange (QString id)
{
    _clean = false;
    QPalette p = _id->palette();
    if (_ids.contains(id)) {
        p.setColor(QPalette::Text, Qt::red);
        _buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        p.setColor(QPalette::Text, Qt::black);
        _buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    _id->setPalette(p);
}
