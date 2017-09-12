#ifndef WINDOWVEDITOR_H
#define WINDOWVEDITOR_H

#include <QMainWindow>
#include <widgetveditor.h>

class WindowVEditor : public QMainWindow
{
    Q_OBJECT
public:
    WindowVEditor(int argc, char *argv[]);

private:
    void createMenu();

signals:

public slots:

private slots:
    void newtab(QString path = "");
    void closetab(int);
    void setFileName(QString filename);

private:
    QTabWidget *tabwidget;
    /*QAction *actionOpenDocument;
    QAction *actionSaveDocument;
    QAction *actionSaveAsDocument;
    QAction *actionPrint;
    QAction *actionPrintPreview2;*/

};

#endif // WINDOWVEDITOR_H
