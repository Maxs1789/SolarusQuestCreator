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
#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "sol/types.h"
#include "exception/SQCException.h"

class Editor : public QMainWindow
{
    Q_OBJECT
public:
    Editor (QString questDir, ResourceType type, QString id);

    QString questDir () const;
    ResourceType type () const;
    QString id () const;

    virtual bool isSaved () const = 0;
    virtual void save (QString dataDirectory) throw(SQCException) = 0;

signals:
    void onSave (Editor *);
    void onClose (Editor *);

protected:
    void closeEvent (QCloseEvent *event);

private:
    QString _questDir;
    ResourceType _type;
    QString _id;
};

#endif
