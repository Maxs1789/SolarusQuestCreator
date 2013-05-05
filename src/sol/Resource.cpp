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
#include "sol/Resource.h"

const QString Resource::p_name = "name";

Resource::Resource (ResourceType type, QString id, QString name) :
    _type(type),
    _id(id),
    _name(name)
{}

ResourceType Resource::type () const
{
    return _type;
}

QString Resource::id() const
{
    return _id;
}

QString Resource::name () const
{
    return _name;
}
