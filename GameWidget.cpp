//
// Created by LMR on 2022/12/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWidget.h" resolved

#include <cmath>
#include <chrono>
#include "GameWidget.h"
#include "ui_GameWidget.h"
#include "RandomShuffle.h"

using namespace std::chrono_literals;

GameWidget::GameWidget(int num, QWidget *parent)
	:
	QWidget(parent),
	ui(new Ui::GameWidget),
	timer(new QTimer()),
	stopTimer(new QTimer())
{
	ui->setupUi(this);

	int col = static_cast<int>(std::sqrt(num));
	qcout<<"num:"<<num<<"col:"<<col<<"sqrt:"<<std::sqrt(num);

	setWindowTitle(QString("%1 宫格 - 舒尔特方格").arg(std::pow(col,2)));

	for (int i = 0, n = 0; i < col; ++i) {
		for (int j = 0; j < col; ++j) {
			QLabel *label = new QLabel(" ", this);
			label->setAlignment(Qt::AlignCenter);
			label->setObjectName("gridLabel");
//			label->setStyleSheet("QLabel{background-color: rgb(255, 85, 0);font-size:24pt}");
			vLabels.push_back(label);
			ui->gridLayout->addWidget(label, i, j);

			vData.push_back(++n);
		}
	}

//	ui->widget->setStyleSheet("background-color: transparent;");
	ui->startBtn->setShortcut(QKeySequence("S"));
	ui->startBtn->setToolTip("快捷键： S ");
	ui->lcdNumber->setDigitCount(8);//设置显示的位数限制

	ui->startBtn->setProperty("status", true);//默认true，开始字样按钮
	connect(ui->startBtn, &QPushButton::clicked, this, &GameWidget::StartBtnClicked);
	connect(ui->returnBtn, &QPushButton::clicked, [this]()
	{
		emit btnClickedSignal(ModeWidgetSignal);
	});
	connect(timer, &QTimer::timeout, this, &GameWidget::UpdateTimeDisplay);
	connect(stopTimer, &QTimer::timeout, this, [this](){
		UpdateLabel(true);
	});
}

GameWidget::~GameWidget()
{
	delete ui;
}
void GameWidget::StartBtnClicked()
{
	if (ui->startBtn->property("status") == true) {
		//切换为运行状态，停止按钮

		UpdateLabel();

		timer->start(1);
		startTime = QTime::currentTime();
		stopTimer->stop();

		ui->startBtn->setText("停止计时（S）");
		ui->startBtn->setProperty("status", false);
		ui->startBtn->setShortcut(QKeySequence("S"));
	}
	else {
		//切换为就绪状态，开始按钮
		timer->stop();
		//启动超过6s数字自动消失
		stopTimer->start(6s);
		ui->startBtn->setText("开始计时（S）");
		ui->startBtn->setProperty("status", true);
		ui->startBtn->setShortcut(QKeySequence("S"));
	}
}
void GameWidget::UpdateTimeDisplay()
{
	QTime current = QTime::currentTime();
	auto millisecond = this->startTime.msecsTo(current); //从基准时间到现在过了多少毫秒
	QTime showTime(0, 0, 0, 0);
	showTime = showTime.addMSecs(millisecond);

	this->ui->lcdNumber->display(showTime.toString("hh:mm:ss:zzz"));

}
void GameWidget::UpdateLabel(bool emptyLabel)
{
	if (emptyLabel) {
		for (auto &it : vLabels) {
			it->setText(" ");
		}
	}
	else {
		RandomShuffle(vData.begin(), vData.end());
		for (int i = 0; i < vLabels.size(); ++i) {
			//两者没区别
//		vLabels[i]->setText(QString::number(vData[i]));
			vLabels[i]->setNum(vData[i]);
		}
	}
}

