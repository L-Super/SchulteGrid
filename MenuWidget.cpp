//
// Created by LMR on 2022/12/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MenuWidget.h" resolved

#include <QLabel>
#include <QMessageBox>
#include <QStackedLayout>
#include "MenuWidget.h"
#include "ui_MenuWidget.h"
#include "fmt/format.h"

MenuWidget::MenuWidget(QWidget *parent)
	:
	QWidget(parent),
	ui(new Ui::MenuWidget),
	stackedLayout(new QStackedLayout()),
	modeWidget(new WhichModeWidget()),
	gameWidget(new GameWidget())
{
	ui->setupUi(this);
	setWindowTitle("舒尔特方格");

	stackedLayout->addWidget(this);
	stackedLayout->addWidget(modeWidget);
	stackedLayout->addWidget(gameWidget);
	stackedLayout->setCurrentWidget(this);

	ui->startBtn->setIcon(QIcon(":/resources/play.png"));
	ui->recordBtn->setIcon(QIcon(":/resources/log.png"));
	ui->helpBtn->setIcon(QIcon(":/resources/help.png"));

	connect(ui->startBtn, &QPushButton::clicked, [this]()
	{
		SwitchWidget(SignalType::ModeWidgetSignal);
	});
	//TODO:
	connect(ui->recordBtn, &QPushButton::clicked, []()
	{
		qcout<<"record";
		fmt::print("db \n");

		auto list = LeveldbPimpl::instance().GetAllData();
		if (list.empty())
			fmt::print("db is empty\n");
		for(auto& it:list)
			fmt::print("data: {}\n",it);
	});
	connect(ui->helpBtn, &QPushButton::clicked, this, &MenuWidget::HelpBtnClick);
	connect(modeWidget, &WhichModeWidget::btnClickedSignal, this, &MenuWidget::SwitchWidget);
	connect(gameWidget, &GameWidget::btnClickedSignal, this, &MenuWidget::SwitchWidget);
}

MenuWidget::~MenuWidget()
{
	delete ui;
}
void MenuWidget::HelpBtnClick()
{
	QMessageBox box;
	box.setWindowTitle("帮助");

	box.setText("舒尔特方格是一种注意力训练方法。");
	QString text{"反复练习，大脑的集中注意力功能就会不断的加固，注意水平越来越高。<br>"
				 "训练时，用手指按 1 ~ n 的顺序依次指出其位置，所用时间越短，注意力水平越高。<br>"
				 "最新版本：<a href='https://github.com/L-Super'>Github</a><br>"
	};

	box.setInformativeText(text);
	box.exec();
}
void MenuWidget::SwitchWidget(SignalType type)
{
	switch (type) {
	case MenuWidgetSignal: {
		stackedLayout->setCurrentWidget(this);
		modeWidget->hide();
		this->show();
	}
		break;
	case GameWidgetSignal: {
		//remove old gameWidget
		stackedLayout->removeWidget(gameWidget);
		disconnect(gameWidget, &GameWidget::btnClickedSignal, this, &MenuWidget::SwitchWidget);
		delete gameWidget;
		//add new gameWidget
		gameWidget = new GameWidget(modeWidget->EnterMode());
		connect(gameWidget, &GameWidget::btnClickedSignal, this, &MenuWidget::SwitchWidget);
		stackedLayout->addWidget(gameWidget);

		stackedLayout->setCurrentWidget(gameWidget);
		modeWidget->hide();
	}
		break;
	case ModeWidgetSignal: {
		stackedLayout->setCurrentWidget(modeWidget);
		this->hide();
		gameWidget->hide();
	}
		break;
	}
}
