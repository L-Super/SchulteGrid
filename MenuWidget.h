//
// Created by LMR on 2022/12/11.
//

#ifndef SCHULTEGRID_MENUWIDGET_H
#define SCHULTEGRID_MENUWIDGET_H

#include <QWidget>

#include "Common.h"
#include "GameWidget.h"
#include "WhichModeWidget.h"

class QStackedLayout;

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuWidget;
}
QT_END_NAMESPACE

class MenuWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MenuWidget(QWidget* parent = nullptr);

  ~MenuWidget() override;

protected:
  void HelpBtnClick();
  void SwitchWidget(SignalType type);

signals:
  void switchWidgetSignal(SignalType type);

private:
  Ui::MenuWidget* ui;
  QStackedLayout* stackedLayout;
  WhichModeWidget* modeWidget;
  GameWidget* gameWidget;
};

#endif  // SCHULTEGRID_MENUWIDGET_H
