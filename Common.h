//
// Created by LMR on 2022/12/12.
//

#ifndef COMMON_H
#define COMMON_H
#include <QDebug>
#include <QFileInfo>

#define qcout qDebug() << "[" << __FILE__ << __func__ << __LINE__ << "]"

/**
 * 信号类型，用于切换界面
 */
enum SignalType
{
  MenuWidgetSignal,
  GameWidgetSignal,
  ModeWidgetSignal
};

/**
 * 自定义单元格Type的类型，在创建单元格的item时使用
 */
enum TABLE_ITEM_TYPE
{
  DATE,
  MODE,
  TIME
};

#endif  // COMMON_H
