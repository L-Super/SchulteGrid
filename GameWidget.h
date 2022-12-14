//
// Created by LMR on 2022/12/11.
//

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include "Common.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class GameWidget;
}
QT_END_NAMESPACE

class GameWidget: public QWidget
{
Q_OBJECT

public:
	explicit GameWidget(int num = 9, QWidget *parent = nullptr);
	~GameWidget() override;

public:
	void StartBtnClicked();
	void UpdateTimeDisplay();
	void UpdateLabel(bool emptyLabel = false);

signals:
	void btnClickedSignal(SignalType type);

private:
	Ui::GameWidget *ui;
	QVector<QLabel *> vLabels;// QLabel 集合
	QTimer *timer;// 用时计时器
	QTimer* stopTimer;// 停止计时后触发操作的计时器
	QTime startTime;
	std::vector<int> vData;
};


#endif //GAMEWIDGET_H