#pragma once

#include <QObject>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QHexEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QHexEditPlugin")

public:
    QHexEditPlugin(QObject * parent = nullptr);

    bool isContainer() const override;
    bool isInitialized() const override;
    auto icon() const  ->QIcon override;
    auto domXml() const  -> QString override;
    auto group() const ->QString override;
    auto includeFile() const ->QString override;
    auto name() const ->QString override;
    auto toolTip() const ->QString override;
    auto whatsThis() const ->QString override;
    auto createWidget(QWidget *parent) ->QWidget* override;
    void initialize(QDesignerFormEditorInterface *core) override;

private:
    bool initialized;
};
