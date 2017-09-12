#include "windowveditor.h"
#include "iostream"

using namespace std;

WindowVEditor::WindowVEditor(int argc, char *argv[])
{
#ifdef Q_OS_OSX
    setUnifiedTitleAndToolBarOnMac(true);
#endif

    setWindowTitle("VEditor");

    setWindowIcon(QIcon("image/VEditor"));

    tabwidget = new QTabWidget();

    QWidget *container = new QWidget;

    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(0);

    container->setLayout(layout);

    layout->addWidget(tabwidget);

    tabwidget->setTabShape(QTabWidget::Rounded);

    QPushButton *cornerWidget = new QPushButton;

    cornerWidget->setIcon(QIcon("images/new-tab"));

    cornerWidget->setIconSize(QSize(25, 25));

    cornerWidget->setFlat(true);

    tabwidget->setCornerWidget(cornerWidget, Qt::TopLeftCorner);

    tabwidget->setTabsClosable(true);

    tabwidget->setMovable(true);

    setCentralWidget(container);

    newtab(QString(argv[1]));



    connect(tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closetab(int)));

    connect(cornerWidget, SIGNAL(clicked(bool)) , this, SLOT(newtab()));
}


void WindowVEditor::newtab(QString path)
{
    WidgetVEditor *veditor = new WidgetVEditor(path);

    if(path != "")
        tabwidget->addTab(veditor, path);
    else
        tabwidget->addTab(veditor, "untitled");
    tabwidget->setCurrentIndex(tabwidget->currentIndex()+1);

    connect(veditor, SIGNAL(currentFileName(QString)), this, SLOT(setFileName(QString)));
}

void WindowVEditor::closetab(int tab)
{
    if(!qobject_cast<WidgetVEditor *>(tabwidget->currentWidget())->maybeSave()){

    }else{
        if(tabwidget->count() == 1)
            qApp->quit();
        else
            tabwidget->removeTab(tab);
    }
}

void WindowVEditor::setFileName(QString filename)
{
    qDebug() << filename;
    QFileInfo fileInfo(filename);
    tabwidget->setTabText(tabwidget->currentIndex(), fileInfo.fileName());
}
