#ifndef WIDGETVEDITOR_H
#define WIDGETVEDITOR_H

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

#include <QtGui>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QtWidgets>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QSettings>

/*
 * Classe de creation de la fenêtre principale
 * Elle herite de QmainWindow
 */


class WidgetVEditor : public QWidget
{
    Q_OBJECT

    public:
        WidgetVEditor(QString path);
        bool maybeSave();

    private:
        void createMenus();
        void createToolBars();
        void createStatusBar();
        void setStyle(int style);

    public slots:
        void print();
        void DocumentPrintPreview();
        void printPreview(QPrinter *printer);
        void openDocument();
        bool saveDocument();
        bool saveAsDocument();
        void exportAsPdf();
        void exportAsOdt();

    private slots:
        void setTextColor();
        void setTextBackground();
        void setTextBold();
        void setTextItalic();
        void setTextUnderline();
        void setTextStrikeOut();
        void setTextSize(const QString &p);
        void setTextFont(const QString &f);
        void setTextAlign(QAction *a);
        void aboutVEditor();
        void License();
        void unlockToolBar(bool p);
        void disableUnlockToolBar();
        void redoAvailable(bool yes);
        void undoAvailable(bool yes);
        void clear();
        void styleDarked(bool styleDarkTrueFalse);
        void cursorPositionChanged();
        void textAlignmentChanged(Qt::Alignment a);
        void slotbrutOuHtml();

    signals:
        void currentFileName(QString filename);

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        void setCurrentFileName(const QString &fileName);
        void currentCharFormatChanged(const QTextCharFormat &format);
        void fontChanged(const QFont &f);
        void colorChanged(const QColor &c);
        void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

        QVBoxLayout *mainLayout; // layout principal
        QTextEdit *texte; // la zone de texte
        QToolBar *toolBar; // barre d'outils haute
        QToolBar *toolBar2; // barre d'outils basse
        QStatusBar *statusBar; // barre de status
        QComboBox *comboSize; // spinbox pour choisir la taille de la police
        QFontComboBox *comboFont;
        QString fileName; // chemin du fichier enregistré
        int taillepolice; // taille de la police
        int nombreDeCaracteres;
        int nombreDeCaracteresActuel;
        int nombreDoc;
        int currentStyle; // le style actuel de l'application
        QActionGroup *alignGroup;
        QAction *actionUnlockToolBar;
        QAction *actionOpenDocument;
        QAction *actionSaveDocument;
        QAction *actionSaveAsDocument;
        QAction *actionPrint;
        QAction *actionPrintPreview;
        QAction *actionExportAsPdf;
        QAction *actionExportAsOdt;
        QAction *actionQuit;
        QAction *actionUndo;
        QAction *actionRedo;
        QAction *actionClear;
        QAction *styleBold;
        QAction *styleItalic;
        QAction *styleUnderline;
        QAction *styleStrikeOut;
        QAction *actionAlignLeft;
        QAction *actionAlignRight;
        QAction *actionAlignJustify;
        QAction *actionAlignCenter;
        QAction *styleColor;
        QAction *styleTextBackground;
        QAction *actionSelectAll;
        QAction *actionCopy;
        QAction *actionPaste;
        QAction *actionCut;
        QAction *brutOuHtml;
        QSettings *settingsToolBar;
        bool styleDark;


};

#endif // WIDGETVEDITOR_H
