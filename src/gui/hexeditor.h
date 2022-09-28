#pragma once

#include <qhexedit/qhexedit.h>


// an editor lives inside an EditorTab, we have have different kinds of editors. Text editors but also hex editors.
class Editor
{
public:
    virtual ~Editor() = default;
    virtual void Save() = 0;
    virtual void SaveAs() = 0;
    //virtual void Close() = 0;
    virtual auto Filepath() const -> QString = 0;
    virtual auto Filename() const -> QString = 0;
};

// glue object to handle file handler and the hexeditor
class hexeditor : public Editor, public QHexEdit
{
    Q_OBJECT
public:
    // create new empty
    hexeditor(QWidget* parent = nullptr);
    // load file
    hexeditor(QString filename, QWidget* parent = nullptr);

    void Save() override;
    void SaveAs() override;

    auto Filepath() const -> QString override;
    auto Filename() const -> QString override;

private:
    bool savefile(const QString& fileName);

    QString filename_{};
    QFile file_{};
    bool is_untitled_{true};
};
