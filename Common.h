//
// Created by LMR on 2022/12/12.
//

#ifndef COMMON_H
#define COMMON_H
#include <QDebug>
#include <QFileInfo>

#define qcout qDebug()<<"["<<__FILE__<<__func__<<__LINE__<<"]"

enum SignalType{
	MenuWidgetSignal,
	GameWidgetSignal,
	ModeWidgetSignal
};
#endif //COMMON_H
