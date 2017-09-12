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


#include "widgetveditor.h"
#include "aboutveditor.h"
#include "license.h"
#include <QPrintPreviewDialog>

WidgetVEditor::WidgetVEditor(QString path)
{

    /*qDebug() << "argc : " << path;

    for(int i = 0; i < path; i++){
        qDebug() << "argv" << i << " : " << argv[i];
    }*/

    // WINDOW

    setWindowTitle("VEditor");

    setWindowIcon(QIcon("images/VEditor.png"));


    // MAIN LAYOUT

    mainLayout = new QVBoxLayout;

    setLayout(mainLayout);

    mainLayout->setContentsMargins(0, 0, 0, 0);


    // QTEXTEDIT

    texte = new QTextEdit(this);

    if(path != 0){
        QString nomFichier = path;

            QFile fichier(nomFichier); // On crée encore et toujours notre objet QFile en précisant le chemin du fichier
            if (fichier.open(QIODevice::ReadOnly)) // Cette fois-ci c'est le flag ReadOnly qui est utilisé, cependant lui si le fichier sélectionné n'existe pas il retournera irrémédiablement false
            {
                texte->setText(fichier.readAll()); // Là on dit au QTextEdit de récupérer TOUTES les données du fichier ouvert via readAll(), de plus la fonction setText() retournera un texte riche et non plus en html

                setWindowTitle(nomFichier + " - VEditor"); // Ici c'est un bonus xD, rien ne t'empêche en effet d'ajouter autant de fonctions que tu veux lors de l'ouverture de ton fichier !
            }
    }


            // Ouvrir
            actionOpenDocument = new QAction("&Open");
            actionOpenDocument->setShortcut(QKeySequence("Ctrl+O"));
            actionOpenDocument->setIcon(QIcon("images/open"));


            // Enregistrer
            actionSaveDocument = new QAction("&Save");
            actionSaveDocument->setShortcut(QKeySequence("Ctrl+S"));
            actionSaveDocument->setIcon(QIcon("images/save"));


            // Enregistrer sous
            actionSaveAsDocument = new QAction("Save &As");
            actionSaveAsDocument->setShortcut(QKeySequence("ctrl+shift+s"));
            actionSaveAsDocument->setIcon(QIcon("images/save-as"));


            // Imprimer
            actionPrint = new QAction("&Print");
            actionPrint->setShortcut(QKeySequence("Ctrl+p"));
            actionPrint->setIcon(QIcon("images/print"));

            // Print preview
            actionPrintPreview = new QAction("Print Pr&eview");
            actionPrintPreview->setShortcut(QKeySequence("Ctrl+shift+o"));
            actionPrintPreview->setIcon(QIcon("images/print-preview"));


            actionExportAsPdf = new QAction("Export as pdf");
            actionExportAsPdf->setShortcut(QKeySequence("-"));
            actionExportAsPdf->setIcon(QIcon("images/export-pdf"));


            actionExportAsOdt = new QAction("Export as odt");
            actionExportAsOdt->setShortcut(QKeySequence("-"));
            actionExportAsOdt->setIcon(QIcon("images/export-odt"));


            // enregistrer en texte brut ou en html
            brutOuHtml = new QAction("Save as plain text");
            brutOuHtml->setCheckable(true);

            // Quitter
            actionQuit = new QAction("&Quit");
            actionQuit->setShortcut(QKeySequence("Ctrl+Q"));
            actionQuit->setIcon(QIcon("images/quit"));
             // CONNEXION

    // Menu "Edition"
    //QMenu *menuEdition = menuBar()->addMenu("&Edition");
        // Menu Edition - Sous menus


            // Undo
            actionUndo = new QAction("&Undo");
            actionUndo->setIcon(QIcon("images/undo"));
            actionUndo->setShortcut(QKeySequence("Ctrl+Z"));
            actionUndo->setDisabled(true);

            // Redo
            actionRedo = new QAction("&Redo");
            actionRedo->setIcon(QIcon("images/redo"));
            actionRedo->setShortcut(QKeySequence("Ctrl+Shift+Z"));
            actionRedo->setDisabled(true);

            // Clear
            actionClear = new QAction("Clear");
            actionClear->setShortcut(QKeySequence("Ctrl+D"));
            actionClear->setIcon(QIcon("images/clear"));

            // Gras

            styleBold = new QAction("Gras");
            styleBold->setIcon(QIcon("images/bold"));
            styleBold->setCheckable(true);


            // Italique
            styleItalic = new QAction("Italic");
            styleItalic->setIcon(QIcon("images/italic"));
            styleItalic->setCheckable(true);


            // Souligne
            styleUnderline = new QAction("Underline");
            styleUnderline->setIcon(QIcon("images/underline"));
            styleUnderline->setCheckable(true);

            // StrikeOut
            styleStrikeOut = new QAction("StrikeOut");
            styleStrikeOut->setIcon(QIcon("images/strike-out"));
            styleStrikeOut->setCheckable(true);


            // Qt::AlignLeft
            actionAlignLeft = new QAction("Align Left");
            actionAlignLeft->setIcon(QIcon("images/align-left"));
            actionAlignLeft->setCheckable(true);


            // Qt::AlignRight
            actionAlignRight = new QAction("Align Right");
            actionAlignRight->setIcon(QIcon("images/align-right"));
            actionAlignRight->setCheckable(true);


            // Qt::AlignJustify
            actionAlignJustify = new QAction("Align Justify");
            actionAlignJustify->setIcon(QIcon("images/align-justify"));
            actionAlignJustify->setCheckable(true);


            // Qt::AlignCenter
            actionAlignCenter = new QAction("Align Center");
            actionAlignCenter->setIcon(QIcon("images/align-center"));
            actionAlignCenter->setCheckable(true);

            // Make sure the alignLeft  is always left of the alignRight
            alignGroup = new QActionGroup(this);
            connect(alignGroup, &QActionGroup::triggered, this, &WidgetVEditor::setTextAlign);

            if (QApplication::isLeftToRight()) {
                alignGroup->addAction(actionAlignLeft);
                alignGroup->addAction(actionAlignCenter);
                alignGroup->addAction(actionAlignRight);
            } else {
                alignGroup->addAction(actionAlignRight);
                alignGroup->addAction(actionAlignCenter);
                alignGroup->addAction(actionAlignLeft);
            }
            alignGroup->addAction(actionAlignJustify);


            // Barre
            //QAction *styleBarre = menuEdition->addAction("Barré");
            //styleBarre->setIcon(QIcon("images/barré.png"));
            //styleBarre->setCheckable(true);

            // Couleur
            QPixmap pix(16, 16);
            pix.fill(Qt::black);
            styleColor = new QAction(pix, "color");
            styleColor->setIcon(QIcon("images/color.png"));

            styleTextBackground = new QAction("highligh");
            styleTextBackground->setIcon(QIcon("images/highligh"));

            actionSelectAll = new QAction("Select all");
            actionSelectAll->setIcon(QIcon("images/select-all"));

            actionCopy = new QAction("Copy");
            actionCopy->setIcon(QIcon("images/copy"));

            actionPaste = new QAction("Paste");
            actionPaste->setIcon(QIcon("images/paste"));

            actionCut = new QAction("Cut");
            actionCut->setIcon(QIcon("images/cut"));




    // Menu "Affichage"
    //QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

            // cacher la barre
            QAction *cacherToolBarHaute = new QAction("Cacher la barre d'outils haute", this);
            cacherToolBarHaute->setCheckable(true);
            //menuAffichage->addAction(cacherToolBarHaute);


            QAction *cacherToolBarBasse = new QAction("Cacher la barre d'outils basse", this);
            cacherToolBarBasse->setCheckable(true);
            //menuAffichage->addAction(cacherToolBarBasse);


            QAction *afficherStatusBar = new QAction("Afficher la barre de status", this);
            afficherStatusBar->setCheckable(true);
            //menuAffichage->addAction(afficherStatusBar);

            actionUnlockToolBar = new QAction("Déverrouiller les barres d'outils", this);
            actionUnlockToolBar->setCheckable(true);
            //menuAffichage->addAction(actionDeverrouillerToolBar);


            QAction *actionStyleDark = new QAction("Appliquer un thème sombre", this);
            actionStyleDark->setCheckable(true);
            //menuAffichage->addAction(actionStyleDark);






    // Menu "Aide"
    //QMenu *menuAide = menuBar()->addMenu("&Aide");

            // About QT
            QAction *actionAboutQT = new QAction("&A propos de QT", this);
            //menuAide->addAction(actionAboutQT);
            actionAboutQT->setIcon(QIcon("images/QT.png"));

            // About VEditor
            QAction *actionAboutVEditor = new QAction("&A propos de VEditor", this);
            //menuAide->addAction(actionAboutVEditor);
            actionAboutVEditor->setIcon(QIcon("images/VEditor.png"));

            // License
            QAction *actionLicense = new QAction("license", this);
            //menuAide->addAction(actionLicense);
            actionLicense->setIcon(QIcon("images/GPLv3"));



    // barre d'outils
    createToolBars();

    toolBar->setIconSize(QSize(25, 25));

    // Barre de status
    createStatusBar();



    // Connection au slots
        // menu fichier
        //connect(actionNewDocument, SIGNAL(triggered()), this, SLOT(newDocument()));
        connect(actionOpenDocument, SIGNAL(triggered()), this, SLOT(openDocument()));
        connect(actionSaveDocument, SIGNAL(triggered()), this, SLOT(saveDocument()));
        connect(actionSaveAsDocument, SIGNAL(triggered()), this, SLOT(saveAsDocument()));
        connect(brutOuHtml, SIGNAL(triggered()), this, SLOT(slotbrutOuHtml()));
        connect(actionPrint, SIGNAL(triggered()), this, SLOT(print()));
        connect(actionPrintPreview, SIGNAL(triggered()), this, SLOT(DocumentPrintPreview()));
        connect(actionExportAsPdf, SIGNAL(triggered(bool)), this, SLOT(exportAsPdf()));
        connect(actionExportAsOdt, SIGNAL(triggered(bool)), this, SLOT(exportAsOdt()));
        connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));


        // menu edition
        connect(actionUndo, SIGNAL(triggered()), texte, SLOT(undo()));
        connect(actionRedo, SIGNAL(triggered()), texte, SLOT(redo()));
        connect(texte, SIGNAL(redoAvailable(bool)), this, SLOT(redoAvailable(bool)));
        connect(texte, SIGNAL(undoAvailable(bool)), this, SLOT(undoAvailable(bool)));
        connect(actionClear, SIGNAL(triggered()), this, SLOT(clear()));
        connect(styleBold, SIGNAL(triggered(bool)), this, SLOT(setTextBold()));
        connect(styleItalic, SIGNAL(triggered(bool)), this, SLOT(setTextItalic()));
        connect(styleUnderline, SIGNAL(triggered(bool)), this, SLOT(setTextUnderline()));
        connect(styleStrikeOut, SIGNAL(triggered(bool)), this, SLOT(setTextStrikeOut()));
        connect(styleColor, SIGNAL(triggered()), this, SLOT(setTextColor()));
        connect(styleTextBackground, SIGNAL(triggered()), this, SLOT(setTextBackground()));
        connect(actionSelectAll, SIGNAL(triggered()), texte, SLOT(selectAll()));
        connect(actionCopy, SIGNAL(triggered()), texte, SLOT(copy()));
        connect(actionPaste, SIGNAL(triggered()), texte, SLOT(paste()));
        connect(actionCut, SIGNAL(triggered()), texte, SLOT(cut()));

        connect(texte, &QTextEdit::currentCharFormatChanged, this, &WidgetVEditor::currentCharFormatChanged);




        // menu affichage
        connect(actionUnlockToolBar, SIGNAL(triggered(bool)), this, SLOT(unlockToolBar(bool)));
        connect(actionStyleDark, SIGNAL(triggered(bool)), this, SLOT(styleDarked(bool)));

        // menu aide
        connect(actionAboutQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
        connect(actionAboutVEditor, SIGNAL(triggered()), this, SLOT(aboutVEditor()));
        connect(actionLicense, SIGNAL(triggered()), this, SLOT(License()));

    // barre d'outils

        //haute
        connect(cacherToolBarHaute, SIGNAL(triggered(bool)), toolBar, SLOT(setHidden(bool)));
        connect(cacherToolBarHaute, SIGNAL(triggered(bool)), this, SLOT(disableUnlockToolBar()));

        //basse
        connect(cacherToolBarBasse, SIGNAL(triggered(bool)), toolBar2, SLOT(setHidden(bool)));
        connect(cacherToolBarBasse, SIGNAL(triggered(bool)), this, SLOT(disableUnlockToolBar()));

        // barre de status
        connect(afficherStatusBar, SIGNAL(triggered(bool)), statusBar, SLOT(setVisible(bool)));
        connect(texte, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));



        QFont textFont("Helvetica");
        textFont.setStyleHint(QFont::SansSerif);
        texte->setFont(textFont);
        fontChanged(texte->font());
        colorChanged(texte->textColor());
        textAlignmentChanged(texte->alignment());

        texte->setFocus();


    // STYLE SHEET

    styleDark = settingsToolBar->value("style/current").toInt();

    setStyle(styleDark);

    if(currentStyle)
    {

        actionStyleDark->setChecked(true);

    }

    else
    {


        actionStyleDark->setChecked(false);

    }



}

bool WidgetVEditor::maybeSave()
{
    if (!texte->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return saveDocument();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}


void WidgetVEditor::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    texte->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    emit currentFileName(fileName);
}


// SLOT enregistrement des options
void WidgetVEditor::closeEvent(QCloseEvent *event)
{

    settingsToolBar->setValue("style/current", currentStyle);

    event->accept();

}

// SLOT Style dark
void WidgetVEditor::styleDarked(bool styleDarkTrueFalse)
{
    setStyle(styleDarkTrueFalse);
}

// SLOT position du curseur
void WidgetVEditor::cursorPositionChanged()
{
    textAlignmentChanged(texte->alignment());
}

void WidgetVEditor::textAlignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        actionAlignJustify->setChecked(true);
}

// SLOT Désactiver déverrouiller les barre d'outils
void WidgetVEditor::disableUnlockToolBar()
{

    if(toolBar->isHidden() && toolBar2->isHidden())
    {

        actionUnlockToolBar->setDisabled(true);

    }

    else

    {

        actionUnlockToolBar->setDisabled(false);

    }


}


// SLOT imprimer
void WidgetVEditor::print()
{

    QPrinter * imprimante = new QPrinter;

    QPrintDialog * dialogue = new QPrintDialog(imprimante, this);

    if(dialogue->exec() == QDialog::Accepted)
        texte->print(imprimante);

}


void WidgetVEditor::DocumentPrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &WidgetVEditor::printPreview);
    preview.exec();
}

void WidgetVEditor::printPreview(QPrinter *printer)
{
    texte->print(printer);
}


// SLOT ouvrirDocument
void WidgetVEditor::openDocument()
{
        fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString()); // On récupère donc dans nomFichier le chemin du fichier à ouvrir via le dialogue (PS : ce n'est pas le même que pour enregistrer())

        QFile file(fileName); // On crée encore et toujours notre objet QFile en précisant le chemin du fichier
        if (file.open(QIODevice::ReadOnly)) // Cette fois-ci c'est le flag ReadOnly qui est utilisé, cependant lui si le fichier sélectionné n'existe pas il retournera irrémédiablement false
        {
            QByteArray data = file.readAll();
            QTextCodec *codec = Qt::codecForHtml(data);
            QString str = codec->toUnicode(data);
            if (Qt::mightBeRichText(str)) {
                texte->setHtml(str);
            } else {
                str = QString::fromLocal8Bit(data);
                texte->setPlainText(str);
            }

            setCurrentFileName(fileName);
        }
}


// SLOT enregistrer
bool WidgetVEditor::saveDocument()
{
    if (fileName.isEmpty())
        return saveAsDocument();
    if (fileName.startsWith(QStringLiteral(":/")))
        return saveAsDocument();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(texte->document());
    if (success) {
        texte->document()->setModified(false);
        statusBar->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar->showMessage(tr("Could not write to file \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

// SLOT enregistrerSous
bool WidgetVEditor::saveAsDocument()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "text/html" << "text/plain" << "application/vnd.oasis.opendocument.text";
    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.setDefaultSuffix("html");
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    return saveDocument();
}


void WidgetVEditor::exportAsPdf()
{
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    texte->document()->print(&printer);
}

void WidgetVEditor::exportAsOdt()
{
    QFileDialog fileDialog(this, tr("Export ODT"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/vnd.oasis.opendocument.text"));
    fileDialog.setDefaultSuffix("odt");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    QTextDocumentWriter writer(fileName);
    writer.write(texte->document());
}


// SLOT changerCouleur
void WidgetVEditor::setTextColor()
{
    QColor couleur = QColorDialog::getColor(Qt::white, this); // Ici ta variable va donc stocker la réponse du dialogue qui renverra un QColor

    texte->setTextColor(couleur); // Lequel nous passons à la fonction setTextColor qui définit la couleur du texte
}


// SLOT change texte background
void WidgetVEditor::setTextBackground()
{
    QColor couleur = QColorDialog::getColor(Qt::white, this); // Ici ta variable va donc stocker la réponse du dialogue qui renverra un QColor

    texte->setTextBackgroundColor(couleur); // Lequel nous passons à la fonction setTextColor qui définit la couleur du texte
}


// SLOT verrouiller la barre
void WidgetVEditor::unlockToolBar(bool p)

{
   if (!p)
   {

       toolBar->setMovable(false);
       toolBar2->setMovable(false);

   }
   else
   {

       toolBar->setMovable(true);
       toolBar2->setMovable(true);

   }

}


// SLOT mettreEnGras
void WidgetVEditor::setTextBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(styleBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void WidgetVEditor::setTextItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(styleItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void WidgetVEditor::setTextUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(styleUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void WidgetVEditor::setTextStrikeOut()
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(styleStrikeOut->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

// SLOT clear

void WidgetVEditor::clear()
{

    int reponse = QMessageBox::question(this, "Effacer tout", "Voulez vous vraiment tout effacer?", QMessageBox ::Yes | QMessageBox::No);


    if (reponse == QMessageBox::Yes)

    {

        texte->clear();

    }

}

// texte brut ou html
void WidgetVEditor::slotbrutOuHtml()
{
    styleUnderline->setDisabled(true);
    styleItalic->setDisabled(true);
    styleBold->setDisabled(true);
}

// SLOT taille police
void WidgetVEditor::setTextSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}


// SLOT changer police
void WidgetVEditor::setTextFont(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);

}

void WidgetVEditor::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    styleBold->setChecked(f.bold());
    styleItalic->setChecked(f.italic());
    styleUnderline->setChecked(f.underline());
    styleStrikeOut->setChecked(f.strikeOut());
}

void WidgetVEditor::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    styleColor->setIcon(pix);
}

void WidgetVEditor::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void WidgetVEditor::setTextAlign(QAction *a)
{
    if (a == actionAlignLeft)
        texte->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        texte->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        texte->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        texte->setAlignment(Qt::AlignJustify);
}


void WidgetVEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = texte->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    texte->mergeCurrentCharFormat(format);
}


//implementation de About VEditor
void WidgetVEditor::aboutVEditor()

{

    AboutVEditor *Apropos = new AboutVEditor;
    Apropos->show();

}

// SLOT about License

void WidgetVEditor::License()
{
    AboutLicense *fenetreLicense = new AboutLicense(this);
    fenetreLicense->exec();
}

void WidgetVEditor::setStyle(int style)
{
    /*if(style)
    {

        texte->setStyleSheet("color: #ffffff; background-color: #232629; border-radius: 2");

        setStyleSheet("QTextEdit { border: 1px solid #3daee9 } QTextEdit:hover { border: 1px solid #62c0f1 }");

        toolBar->setStyleSheet("color: #ffffff; background-color: #31363b");

        toolBar2->setStyleSheet("color: #ffffff; background-color: #31363b");

        statusBar->setStyleSheet("color: #ffffff; background-color: #31363b");

        //menuBar()->setStyleSheet("color: #ffffff; background-color: #31363b");

        // Application d'icones claires

        //actionNewDocument->setIcon(QIcon("images/nouveaudocumentb.png"));

        actionOpenDocument->setIcon(QIcon("images/ouvrirdocumentb.png"));

        actionSaveDocument->setIcon(QIcon("images/enregistrerb.png"));

        actionSaveAsDocument->setIcon(QIcon("images/enregistrersousb.png"));

        actionPrint->setIcon(QIcon("images/imprimerb.png"));

        actionQuit->setIcon(QIcon("images/quitterb.png"));

        actionUndo->setIcon(QIcon("images/undob.png"));

        actionRedo->setIcon(QIcon("images/redob.png"));

        styleBold->setIcon(QIcon("images/grasb.png"));

        styleItalic->setIcon(QIcon("images/italiqueb.png"));

        styleUnderline->setIcon(QIcon("images/soulignerb.png"));

        actionAlignLeft->setIcon(QIcon("images/alignLeftb"));

        actionAlignRight->setIcon(QIcon("images/alignRightb"));

        actionAlignJustify->setIcon(QIcon("images/alignJustifyb"));

        actionAlignCenter->setIcon(QIcon("images/alignCenterb"));

        styleColor->setIcon(QIcon("images/couleurb.png"));

        currentStyle = 1;
    }
    else
    {
        texte->setStyleSheet("");

        toolBar->setStyleSheet("");

        toolBar2->setStyleSheet("");

        statusBar->setStyleSheet("");

        //menuBar()->setStyleSheet("");

        // Application d'icones sombres

        //actionNewDocument->setIcon(QIcon(QIcon::fromTheme("document-new")));

        actionOpenDocument->setIcon(QIcon(QIcon::fromTheme("document-open")));

        actionSaveDocument->setIcon(QIcon(QIcon::fromTheme("document-save")));

        actionSaveAsDocument->setIcon(QIcon(QIcon::fromTheme("document-save-as")));

        actionPrint->setIcon(QIcon(QIcon::fromTheme("document-print")));

        actionQuit->setIcon(QIcon(QIcon::fromTheme("application-exit")));

        actionUndo->setIcon(QIcon(QIcon::fromTheme("edit-undo")));

        actionRedo->setIcon(QIcon(QIcon::fromTheme("edit-redo")));

        styleBold->setIcon(QIcon(QIcon::fromTheme("format-text-bold")));

        styleItalic->setIcon(QIcon(QIcon::fromTheme("format-text-italic")));

        styleUnderline->setIcon(QIcon(QIcon::fromTheme("format-text-underline")));

        actionAlignLeft->setIcon(QIcon(QIcon::fromTheme("format-justify-left")));

        actionAlignRight->setIcon(QIcon(QIcon::fromTheme("format-justify-right")));

        actionAlignJustify->setIcon(QIcon(QIcon::fromTheme("format-justify-fill")));

        actionAlignCenter->setIcon(QIcon(QIcon::fromTheme("format-justify-center")));

        //styleColor->setIcon(QIcon(QIcon::fromTheme("format-text-color")));

        styleTextBackground->setIcon(QIcon(QIcon::fromTheme("format-fill-color")));

        currentStyle = 0;

    }*/


}

// SLOT creer les menus
void WidgetVEditor::createMenus()
{

}
// SLOT creer les barres
void WidgetVEditor::createToolBars()
{
    // LA BARRE D'OUTILS HAUTE
    toolBar = new QToolBar("Afficher la barre d'outils haute");
    mainLayout->addWidget(toolBar);
    //addToolBar(Qt::TopToolBarArea, toolBar);
    settingsToolBar = new QSettings("VEditor", "toolBar");
    toolBar->setMovable(false);
    //toolBar->addAction(actionNewDocument);
    toolBar->addAction(actionOpenDocument);
    toolBar->addAction(actionSaveDocument);
    toolBar->addAction(actionSaveAsDocument);
    toolBar->addSeparator();

    toolBar->addAction(actionPrint);
    toolBar->addAction(actionPrintPreview);
    toolBar->addAction(actionExportAsPdf);
    toolBar->addAction(actionExportAsOdt);
    toolBar->addSeparator();

    comboFont = new QFontComboBox;
    toolBar->addWidget(comboFont);
    connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &WidgetVEditor::setTextFont);


    comboSize = new QComboBox;
    comboSize->setEditable(true);
    toolBar->addWidget(comboSize);
    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &WidgetVEditor::setTextSize);
    toolBar->addSeparator();
    toolBar->addAction(styleBold);
    toolBar->addAction(styleItalic);
    toolBar->addAction(styleUnderline);
    toolBar->addAction(styleStrikeOut);
    toolBar->addSeparator();
    toolBar->addAction(styleColor);
    toolBar->addAction(styleTextBackground);
    toolBar->addSeparator();
    toolBar->addActions(alignGroup->actions());
    toolBar->addSeparator();
    toolBar->addAction(actionUndo);
    toolBar->addAction(actionRedo);



    // LA BARRE D'OUTILS BASSE
    toolBar2 = new QToolBar("Afficher barre d'outils basse");
    mainLayout->addWidget(texte);
    mainLayout->addWidget(toolBar2);
    //addToolBar(Qt::BottomToolBarArea, toolBar2);
    toolBar2->setMovable(false);
    toolBar2->addAction(actionSelectAll);
    toolBar2->addAction(actionCopy);
    toolBar2->addAction(actionPaste);
    toolBar2->addAction(actionCut);
    toolBar2->addAction(actionClear);


}
// SLOT creer barre de status
void WidgetVEditor::createStatusBar()
{
    statusBar = new QStatusBar;
    statusBar->showMessage("");
    mainLayout->addWidget(statusBar);
    statusBar->setHidden(true);
    resize(548, 600);
}


void WidgetVEditor::redoAvailable(bool yes)
{
    if(yes){
        actionRedo->setDisabled(false);
    }
    else{
        actionRedo->setDisabled(true);
    }
}

void WidgetVEditor::undoAvailable(bool yes)
{
    if(yes){
        actionUndo->setDisabled(false);
    }
    else{
        actionUndo->setDisabled(true);
    }
}
