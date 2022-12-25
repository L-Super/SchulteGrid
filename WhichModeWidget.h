//
// Created by LMR on 2022/12/11.
// 选择模式 9宫格 16宫格等
//

#ifndef SCHULTEGRID_WHICHMODEWIDGET_H
#define SCHULTEGRID_WHICHMODEWIDGET_H

#include <QButtonGroup>
#include <QWidget>

#include "Common.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WhichModeWidget;
}
QT_END_NAMESPACE

class WhichModeWidget : public QWidget
{
  Q_OBJECT

public:
  explicit WhichModeWidget(QWidget* parent = nullptr);

  ~WhichModeWidget() override;

public:
  int EnterMode();
  void EnterPushButtonClicked();

signals:
  void btnClickedSignal(SignalType type);

private:
  Ui::WhichModeWidget* ui;
  QButtonGroup* radioBtnGroup;
};

#endif  // SCHULTEGRID_WHICHMODEWIDGET_H
