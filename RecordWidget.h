//
// Created by LMR on 2022/12/24.
//

#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class RecordWidget;
}
QT_END_NAMESPACE

class RecordWidget : public QWidget
{
  Q_OBJECT

public:
  explicit RecordWidget(QWidget* parent = nullptr);
  ~RecordWidget() override;

  /**
   * 初始化QTableWidget属性
   */
  void InitTableWidgetProperty();

  /**
   * 	初始化表头
   */
  void InitTableHeader();

  /**
   * 创建一行的item单元格集合，即一行有三个item
   * @param row 行号
   * @param date 日期
   * @param mode 模式
   * @param time 游戏用时
   */
  void CreateRowItem(int row, const QDateTime& date, const QString& mode, const QString& time);

  /**
   * 从数据末行追加一行数据，由mRowCount记录已有数据行数。
   * @note
   * ui->tableWidget->rowCount()插入方式，是初始化的表格行数再插入一行，而此函数是在已存在数据行下面插入一行
   * @param date 日期
   * @param mode 模式
   * @param time 游戏用时
   */
  void AppendRowItem(const QDateTime& date, const QString& mode, const QString& time);

  /**
   * 将数据库的数据展示到tableWidget
   */
  void ShowDBDataInTable();

private:
  Ui::RecordWidget* ui;
  int mRowCount{};
};

#endif  // RECORDWIDGET_H
