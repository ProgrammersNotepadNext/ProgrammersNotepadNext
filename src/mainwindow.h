#pragma once

#include "optionsdialog.h"
#include "searchdialog.h"
#include "gui/hexeditor.h"
#include "gui/tabwidget.h"

#include <QMainWindow>

class QAction;
class QMenu;
class QUndoStack;
class QLabel;
class QDragEnterEvent;
class QDropEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    TabWidget* tabWidget() const;

    void openFile(const QString& fileName);

protected:
    void closeEvent(QCloseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void about();
    void dataChanged();
    void open();
    void optionsAccepted();
    void findNext();
    void save();
    void saveAs();
    void setAddress(qint64 address);
    void setOverwriteMode(bool mode);
    void setSize(qint64 size);
    void showOptionsDialog();
    void showSearchDialog();

private:
    void init();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolBars();
    int addTextEditor(hexeditor* editor);
    
    void readSettings();
    //bool saveFile(const QString &fileName);
    void setCurrentFile(const QString& fileName);
    void writeSettings();

    TabWidget* tabWidget_{nullptr};

    QMenu* fileMenu_{nullptr};
    QMenu* editMenu_{nullptr};
    QMenu* helpMenu_{nullptr};

    QToolBar* fileToolBar_{nullptr};
    QToolBar* editToolBar_{nullptr};

    QAction* openAct_{nullptr};
    QAction* saveAct_{nullptr};
    QAction* saveAsAct_{nullptr};
    QAction* saveReadableAction_{nullptr};
    QAction* exitAct_{nullptr};

    QAction* undoAct_{nullptr};
    QAction* redoAct_{nullptr};
    QAction* saveSelectionReadable_{nullptr};

    QAction* aboutAct_{nullptr};
    QAction* aboutQtAct_{nullptr};
    QAction* optionsAct_{nullptr};
    QAction* findAct_{nullptr};
    QAction* findNextAct_{nullptr};

    OptionsDialog* optionsDialog_{nullptr};
    SearchDialog* searchDialog_{nullptr};
    QLabel* lbAddress_{nullptr};
    QLabel* lbAddressName_{nullptr};
    QLabel* lbOverwriteMode_{nullptr};
    QLabel* lbOverwriteModeName_{nullptr};
    QLabel* lbSize_{nullptr};
    QLabel* lbSizeName_{nullptr};
};
