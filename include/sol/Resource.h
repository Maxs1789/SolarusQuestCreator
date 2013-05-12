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
#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>
#include "types.h"

/**
 * @brief Classe abstraite de ressource d'une quête (Quest).
 */
class Resource
{
public:
    /** Constante de notification pour la proriété `name`. */
    static const QString p_name;

    /**
     * @brief Donne le type de la ressource.
     *
     * @return Le type de la ressource.
     */
    ResourceType type () const;
    /**
     * @brief Donne l'identifiant de la ressource.
     *
     * @return L'identifiant de la ressource.
     */
    QString id () const;
    /**
     * @brief Donne le nom de la ressource.
     *
     * @return Le nom de la ressource.
     */
    QString name() const;
    /**
     * @brief Change le nom de la ressource.
     *
     * @param name Le nouveau nom de la ressource
     */
    virtual void setName (QString name) = 0;

protected:
    /** Le nom de la resource. */
    QString _name;

    /**
     * @brief Constructeur de resource.
     *
     * @param type Le type de la resource
     * @param id   L'identifiant de la resource
     * @param name Le nom de la resource
     */
    Resource (ResourceType type, QString id, QString name = "new resource");

private:
    ResourceType _type;
    QString _id;
};

#endif
