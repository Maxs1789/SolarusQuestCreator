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
#ifndef QUEST_EXCEPTION_H
#define QUEST_EXCEPTION_H

#include "SQCException.h"

/**
 * @brief Exception lié à la quête (Quest).
 */
class QuestException : public SQCException
{
public:
    /**
     * @brief Constructeur de l'exception.
     *
     * @param message Message de l'exception
     */
    QuestException (QString message = "") throw() :
        SQCException(message)
    {}
};

#endif
