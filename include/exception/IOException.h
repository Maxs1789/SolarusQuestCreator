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
#ifndef IO_EXCEPTION_H
#define IO_EXCEPTION_H

#include <QObject>
#include "SQCException.h"

/**
 * @brief Exception d'entrée-sortie.
 */
class IOException : public SQCException
{
public:
    /**
     * @brief Type d'une exception d'entrée-sortie.
     */
    enum Type
    {
        FILE_EXISTS,
        FILE_N_EXISTS,
        FILE_N_READ,
        FILE_N_WRITE,
        DIR_EXISTS,
        DIR_N_EXISTS,
        DIR_N_WRITE
    };
    /**
     * @brief Constructeur de l'exception.
     *
     * @param type  Type de l'exception
     * @param name  Nom du fichier ou dossier concerné
     */
    IOException (Type type, QString name = "") throw()
    {
        QString message;
        switch (type) {
        case FILE_EXISTS:
            message = QObject::tr("file '$1' already exists");
            break;
        case FILE_N_EXISTS:
            message = QObject::tr("file '$1' does not exists");
            break;
        case FILE_N_READ:
            message = QObject::tr("cannot read file '$1'");
            break;
        case FILE_N_WRITE:
            message = QObject::tr("cannot create file '$1'");
            break;
        case DIR_EXISTS:
            message = QObject::tr("directory '$1' already exists");
            break;
        case DIR_N_EXISTS:
            message = QObject::tr("directory '$1' does not exists");
            break;
        case DIR_N_WRITE:
            message = QObject::tr("cannot create directory '$1'");
            break;
        default:
            message = "unknow input-output error";
        }
        message.replace("$1", name);
        setMessage(message);
    }
};

#endif
