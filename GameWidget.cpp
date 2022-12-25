//
// Created by LMR on 2022/12/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWidget.h" resolved

#include "GameWidget.h"

#include <chrono>
#include <cmath>

#include "LeveldbPimpl.h"
#include "RandomShuffle.h"
#include "fmt/format.h"
#include "nlohmann/json.hpp"
#include "ui_GameWidget.h"

using namespace std::chrono_literals;
using json = nlohmann::json;

GameWidget::GameWidget(int num, QWidget* parent)
    : QWidget(parent), ui(new Ui::GameWidget), timer(new QTimer()), stopTimer(new QTimer())
{
  ui->setupUi(this);

  int col = static_cast<int>(std::sqrt(num));

  mode = std::pow(col, 2);
  setWindowTitle(QString("%1 宫格 - 舒尔特方格").arg(mode));

  for (int i = 0, n = 0; i < col; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      QLabel* label = new QLabel(" ", this);
      label->setAlignment(Qt::AlignCenter);
      label->setObjectName("gridLabel");
      //			label->setStyleSheet("QLabel{background-color: rgb(255, 85, 0);font-size:24pt}");
      vLabels.push_back(label);
      ui->gridLayout->addWidget(label, i, j);

      vData.push_back(++n);
    }
  }

  ui->startBtn->setShortcut(QKeySequence("S"));
  ui->startBtn->setToolTip("快捷键： S ");
  ui->lcdNumber->setDigitCount(8);  // 设置显示的位数限制

  ui->startBtn->setProperty("status", true);  // 默认true，开始字样按钮
  connect(ui->startBtn, &QPushButton::clicked, this, &GameWidget::StartBtnClicked);
  connect(ui->returnBtn, &QPushButton::clicked, [this]() { emit btnClickedSignal(ModeWidgetSignal); });
  connect(timer, &QTimer::timeout, this, &GameWidget::UpdateTimeDisplay);
  connect(stopTimer, &QTimer::timeout, this, [this]() { UpdateLabel(true); });
}

GameWidget::~GameWidget() { delete ui; }

void GameWidget::StartBtnClicked()
{
  if (ui->startBtn->property("status") == true)
  {
    // 切换为运行状态，停止按钮

    UpdateLabel();

    timer->start(1);
    startTime = QTime::currentTime();
    stopTimer->stop();

    ui->startBtn->setText("停止计时（S）");
    ui->startBtn->setProperty("status", false);
    ui->startBtn->setShortcut(QKeySequence("S"));
  }
  else
  {
    // 切换为就绪状态，开始按钮
    timer->stop();

    // 添加数据到数据库
    AddData2DB(QDateTime::currentDateTime(), mode, gameTime);

    // 启动超过6s数字自动消失
    stopTimer->start(6s);
    ui->startBtn->setText("开始计时（S）");
    ui->startBtn->setProperty("status", true);
    ui->startBtn->setShortcut(QKeySequence("S"));
  }
}
void GameWidget::UpdateTimeDisplay()
{
  QTime current = QTime::currentTime();
  QTime time(0, 0, 0, 0);
  // 从基准时间到现在过了多少毫秒
  gameTime = time.addMSecs(this->startTime.msecsTo(current));

  // qcout<<gameTime;

  this->ui->lcdNumber->display(gameTime.toString("mm:ss.zzz"));
}
void GameWidget::UpdateLabel(bool emptyLabel)
{
  if (emptyLabel)
  {
    for (auto& it : vLabels)
    {
      it->setText(" ");
    }
  }
  else
  {
    RandomShuffle(vData.begin(), vData.end());
    for (int i = 0; i < vLabels.size(); ++i)
    {
      // 两者没区别
      // vLabels[i]->setText(QString::number(vData[i]));
      vLabels[i]->setNum(vData[i]);
    }
  }
}
bool GameWidget::AddData2DB(const QDateTime& nowTime, int mode, const QTime& useTime)
{
  QString now = nowTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
  QString time = useTime.toString("mm:ss.zzz");

  qcout << "now:" << now << "time:" << time;

  json dataJson;
  dataJson = {
      {"data_time", now.toStdString()},
      {"mode", mode},
      {"time", time.toStdString()}};

  qcout << QString::fromStdString(dataJson.dump());
  LeveldbPimpl db;
  if (!db.PutData(now.toStdString(), dataJson.dump()))
  {
    qcout << "put data failed";
    return false;
  }

  return true;
}
