//
// Created by LMR on 2022/12/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WhichMode.h" resolved

#include "WhichModeWidget.h"

#include <QDebug>

#include "GameWidget.h"
#include "MenuWidget.h"
#include "ui_WhichModeWidget.h"

WhichModeWidget::WhichModeWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::WhichModeWidget), radioBtnGroup(new QButtonGroup())
{
  ui->setupUi(this);
  setWindowTitle("选择模式");

  radioBtnGroup->addButton(ui->nineRadioButton, 0);
  radioBtnGroup->addButton(ui->sixteenRadioButton, 1);
  radioBtnGroup->addButton(ui->cutomRadioButton, 2);
  ui->nineRadioButton->setChecked(true);

  connect(ui->retrunBtn, &QPushButton::clicked, [this]() { emit btnClickedSignal(MenuWidgetSignal); });
  connect(ui->enterBtn, &QPushButton::clicked, this, &WhichModeWidget::EnterPushButtonClicked);
}

WhichModeWidget::~WhichModeWidget() { delete ui; }

int WhichModeWidget::EnterMode()
{
  int result{0};
  switch (radioBtnGroup->checkedId())
  {
    case 0:
    {
      // nine grid
      result = 9;
    }
    break;
    case 1:
    {
      // 16 grid
      result = 16;
    }
    break;
    case 2:
    {
      // custom grid
      result = ui->spinBox->value();
    }
    break;
  }
  return result;
}
void WhichModeWidget::EnterPushButtonClicked() { emit btnClickedSignal(GameWidgetSignal); }
