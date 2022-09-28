#include "mainwindow.h"
#include "gui/editortab.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QColorDialog>
#include <QFontDialog>
#include <QDragEnterEvent>
#include <QDropEvent>

MainWindow::MainWindow()
{
    setAcceptDrops(true);
    init();
}

TabWidget* MainWindow::tabWidget() const
{
    return tabWidget_;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    writeSettings();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
        event->accept();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        QList<QUrl> urls = event->mimeData()->urls();
        QString filePath = urls.at(0).toLocalFile();
        openFile(filePath);
        event->accept();
    }
}

void MainWindow::about()
{
}

void MainWindow::dataChanged()
{
    // setWindowModified(hexEdit_->isModified());
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        openFile(fileName);
}

void MainWindow::optionsAccepted()
{
    writeSettings();
    readSettings();
}

void MainWindow::findNext()
{
    searchDialog_->findNext();
}

void MainWindow::save()
{
    tabWidget_->current_editor()->Save();
}

void MainWindow::saveAs()
{
    tabWidget_->current_editor()->SaveAs();
}

void MainWindow::setAddress(qint64 address)
{
    lbAddress_->setText(QString("%1").arg(address, 1, 16));
}

void MainWindow::setOverwriteMode(bool mode)
{
    QSettings settings;
    settings.setValue("OverwriteMode", mode);
    if (mode)
        lbOverwriteMode_->setText(tr("Overwrite"));
    else
        lbOverwriteMode_->setText(tr("Insert"));
}

void MainWindow::setSize(qint64 size)
{
    lbSize_->setText(QString("%1").arg(size));
}

void MainWindow::showOptionsDialog()
{
    optionsDialog_->show();
}

void MainWindow::showSearchDialog()
{
    searchDialog_->show();
}

void MainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose);

    optionsDialog_ = new OptionsDialog(this);
    connect(optionsDialog_, SIGNAL(accepted()), this, SLOT(optionsAccepted()));

    tabWidget_ = new TabWidget(this);
    setCentralWidget(tabWidget_);

    // hexEdit_ = new QHexEdit;
    // setCentralWidget(hexEdit_);
    // connect(hexEdit_, SIGNAL(overwriteModeChanged(bool)), this, SLOT(setOverwriteMode(bool)));
    // connect(hexEdit_, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
    // searchDialog_ = new SearchDialog(hexEdit_, this);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createActions()
{
    openAct_ = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct_->setShortcuts(QKeySequence::Open);
    openAct_->setStatusTip(tr("Open an existing file"));
    connect(openAct_, SIGNAL(triggered()), this, SLOT(open()));

    saveAct_ = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct_->setShortcuts(QKeySequence::Save);
    saveAct_->setStatusTip(tr("Save the document to disk"));
    connect(saveAct_, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct_ = new QAction(tr("Save &As..."), this);
    saveAsAct_->setShortcuts(QKeySequence::SaveAs);
    saveAsAct_->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct_, SIGNAL(triggered()), this, SLOT(saveAs()));

    saveReadableAction_ = new QAction(tr("Save &Readable..."), this);
    saveReadableAction_->setStatusTip(tr("Save document in readable form"));
    connect(saveReadableAction_, SIGNAL(triggered()), this, SLOT(saveToReadableFile()));

    exitAct_ = new QAction(tr("E&xit"), this);
    exitAct_->setShortcuts(QKeySequence::Quit);
    exitAct_->setStatusTip(tr("Exit the application"));
    connect(exitAct_, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // fix it like so that we call undo and redo on the active hex editor

    // undoAct_ = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    // undoAct_->setShortcuts(QKeySequence::Undo);
    // connect(undoAct_, SIGNAL(triggered()), hexEdit_, SLOT(undo()));
    //
    // redoAct_ = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    // redoAct_->setShortcuts(QKeySequence::Redo);
    // connect(redoAct_, SIGNAL(triggered()), hexEdit_, SLOT(redo()));

    aboutAct_ = new QAction(tr("&About"), this);
    aboutAct_->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct_, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct_ = new QAction(tr("About &Qt"), this);
    aboutQtAct_->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    findAct_ = new QAction(QIcon(":/images/find.png"), tr("&Find/Replace"), this);
    findAct_->setShortcuts(QKeySequence::Find);
    findAct_->setStatusTip(tr("Show the Dialog for finding and replacing"));
    connect(findAct_, SIGNAL(triggered()), this, SLOT(showSearchDialog()));

    findNextAct_ = new QAction(tr("Find &next"), this);
    findNextAct_->setShortcuts(QKeySequence::FindNext);
    findNextAct_->setStatusTip(tr("Find next occurrence of the searched pattern"));
    connect(findNextAct_, SIGNAL(triggered()), this, SLOT(findNext()));

    optionsAct_ = new QAction(tr("&Options"), this);
    optionsAct_->setStatusTip(tr("Show the Dialog to select applications options"));
    connect(optionsAct_, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
}

void MainWindow::createMenus()
{
    fileMenu_ = menuBar()->addMenu(tr("&File"));
    fileMenu_->addAction(openAct_);
    fileMenu_->addAction(saveAct_);
    fileMenu_->addAction(saveAsAct_);
    fileMenu_->addAction(saveReadableAction_);
    fileMenu_->addSeparator();
    fileMenu_->addAction(exitAct_);

    editMenu_ = menuBar()->addMenu(tr("&Edit"));
    editMenu_->addAction(undoAct_);
    editMenu_->addAction(redoAct_);
    editMenu_->addAction(saveSelectionReadable_);
    editMenu_->addSeparator();
    editMenu_->addAction(findAct_);
    editMenu_->addAction(findNextAct_);
    editMenu_->addSeparator();
    editMenu_->addAction(optionsAct_);

    helpMenu_ = menuBar()->addMenu(tr("&Help"));
    helpMenu_->addAction(aboutAct_);
    helpMenu_->addAction(aboutQtAct_);
}

void MainWindow::createStatusBar()
{
    // Address Label
    lbAddressName_ = new QLabel();
    lbAddressName_->setText(tr("Address:"));
    statusBar()->addPermanentWidget(lbAddressName_);
    lbAddress_ = new QLabel();
    lbAddress_->setFrameShape(QFrame::Panel);
    lbAddress_->setFrameShadow(QFrame::Sunken);
    lbAddress_->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbAddress_);
    // connect(hexEdit_, SIGNAL(currentAddressChanged(qint64)), this, SLOT(setAddress(qint64)));

    // Size Label
    lbSizeName_ = new QLabel();
    lbSizeName_->setText(tr("Size:"));
    statusBar()->addPermanentWidget(lbSizeName_);
    lbSize_ = new QLabel();
    lbSize_->setFrameShape(QFrame::Panel);
    lbSize_->setFrameShadow(QFrame::Sunken);
    lbSize_->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbSize_);
    // connect(hexEdit_, SIGNAL(currentSizeChanged(qint64)), this, SLOT(setSize(qint64)));

    // Overwrite Mode Label
    lbOverwriteModeName_ = new QLabel();
    lbOverwriteModeName_->setText(tr("Mode:"));
    statusBar()->addPermanentWidget(lbOverwriteModeName_);
    lbOverwriteMode_ = new QLabel();
    lbOverwriteMode_->setFrameShape(QFrame::Panel);
    lbOverwriteMode_->setFrameShadow(QFrame::Sunken);
    lbOverwriteMode_->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbOverwriteMode_);
    // setOverwriteMode(hexEdit_->overwriteMode());

    statusBar()->showMessage(tr("Ready"), 2000);
}

void MainWindow::createToolBars()
{
    fileToolBar_ = addToolBar(tr("File"));
    fileToolBar_->addAction(openAct_);
    fileToolBar_->addAction(saveAct_);
    editToolBar_ = addToolBar(tr("Edit"));
    editToolBar_->addAction(undoAct_);
    editToolBar_->addAction(redoAct_);
    editToolBar_->addAction(findAct_);
}

int MainWindow::addTextEditor(hexeditor* editor)
{
    Tab* tab = new EditorTab(this, editor);

    return tabWidget_->addTab(tab, tab->title());
}

void MainWindow::openFile(const QString& fileName)
{
    auto editor = new hexeditor(fileName, this);

    //    file_.setFileName(fileName);
    //    auto hexedit = new QHexEdit(this);
    //    hexedit->setData(file_);
    tabWidget_->setCurrentIndex(addTextEditor(editor));
    // if (!hexEdit_->setData(file_))
    //{
    //    QMessageBox::warning(this, tr("QHexEdit"),
    //                         tr("Cannot read file %1:\n%2.")
    //                         .arg(fileName)
    //                         .arg(file_.errorString()));
    //    return;
    //}
    // setCurrentFile(fileName);
    // statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(610, 460)).toSize();
    move(pos);
    resize(size);

    // hexEdit_->setAddressArea(settings.value("AddressArea").toBool());
    // hexEdit_->setAsciiArea(settings.value("AsciiArea").toBool());
    // hexEdit_->setHighlighting(settings.value("Highlighting").toBool());
    // hexEdit_->setOverwriteMode(settings.value("OverwriteMode").toBool());
    // hexEdit_->setReadOnly(settings.value("ReadOnly").toBool());
    // hexEdit_->setHexCaps(settings.value("HexCaps").toBool());
    //
    // hexEdit_->setHighlightingColor(settings.value("HighlightingColor").value<QColor>());
    // hexEdit_->setAddressAreaColor(settings.value("AddressAreaColor").value<QColor>());
    // hexEdit_->setSelectionColor(settings.value("SelectionColor").value<QColor>());
    // hexEdit_->setFont(settings.value("WidgetFont").value<QFont>());
    //
    // hexEdit_->setAddressWidth(settings.value("AddressAreaWidth").toInt());
    // hexEdit_->setBytesPerLine(settings.value("BytesPerLine").toInt());
}

void MainWindow::setCurrentFile(const QString& /*fileName*/)
{
    __debugbreak();
    // curFile_ = QFileInfo(fileName).canonicalFilePath();
    // isUntitled_ = fileName.isEmpty();
    // setWindowModified(false);
    // if (fileName.isEmpty())
    //    setWindowFilePath("QHexEdit");
    // else
    //    setWindowFilePath(curFile_ + " - QHexEdit");
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
