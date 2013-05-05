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
#include <iostream>
#include <QApplication>
#include "gui/MainWindow.h"

int main (int argc, char** argv)
{
    try {
        QApplication app(argc, argv);
        MainWindow win;
        win.show();
        return app.exec();
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
}
