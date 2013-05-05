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
#include <QCloseEvent>
#include <QMessageBox>
#include "gui/Editor.h"

Editor::Editor (QString questDir, ResourceType type, QString id) :
    _questDir(questDir),
    _type(type),
    _id(id)
{}

QString Editor::questDir () const
{
    return _questDir;
}

ResourceType Editor::type () const
{
    return _type;
}

QString Editor::id () const
{
    return _id;
}

void Editor::closeEvent (QCloseEvent *event)
{
    if (!isSaved()) {
        int r = QMessageBox::question(
            this, tr("Save resource"),
            tr("Are you sure you want to close without saving this resource ?"),
            QMessageBox::Save | QMessageBox::Ok | QMessageBox::Cancel
        );
        if (r == QMessageBox::Save) {
            emit save(this);
        } else if (r == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }
    emit close(this);
}
