/*
    This file is part of VEditor.

    VEditor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    VEditor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VEditor.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ABOUTVEDITOR_H
#define ABOUTVEDITOR_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>


/*
 * Classe pour la creation
 * de la fenêtre "A propos de VEditor".
 * Elle herite de la classe QWidget de Qt
 * et se compose seulement du constructeur.
 */

class AboutVEditor : public QWidget
{
    public:
        AboutVEditor(); // Constructeur
};

#endif // ABOUTVEDITOR_H
