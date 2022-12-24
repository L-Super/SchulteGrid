//
// Created by LMR on 2022/12/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RecordWidget.h" resolved

#include "RecordWidget.h"

#include <QDateTime>
#include <QMessageBox>

#include "Common.h"
#include "LeveldbPimpl.h"
#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "ui_RecordWidget.h"

RecordWidget::RecordWidget(QWidget* parent) : QWidget(parent), ui(new Ui::RecordWidget) {
  ui->setupUi(this);
  InitTableWidgetProperty();
  InitTableHeader();

  ShowDBDataInTable();

  connect(ui->okBtn, &QPushButton::clicked, this, &RecordWidget::close);
  connect(ui->clearAllBtn, &QPushButton::clicked, this, [this]() {
    // 清空数据
    auto choose = QMessageBox::warning(this, "警告", "确定要清空数据吗？", QMessageBox::Cancel, QMessageBox::Yes);
    if (choose == QMessageBox::Yes) {
      LeveldbPimpl db;
      db.ClearDB();
      ui->tableWidget->clearContents();
      qcout << "clear db";
    }
  });
}

RecordWidget::~RecordWidget() { delete ui; }
void RecordWidget::InitTableWidgetProperty() {
  // 设置行数，必须设置
  ui->tableWidget->setRowCount(0);
  // 表格禁止编辑
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // 设置表格为整行选择
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  // 去除选中虚线框
  ui->tableWidget->setFocusPolicy(Qt::NoFocus);
  // 设置排序
  ui->tableWidget->setSortingEnabled(true);

  //    ui->tableWidget->setShowGrid(false); //设置不显示格子线

  // 设置无边框
  //	ui->tableWidget->setFrameShape(QFrame::NoFrame);
  // 设置表头显示模式,设置拉伸模式
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void RecordWidget::InitTableHeader() {
  QTableWidgetItem* headerItem;
  QStringList headerText;
  // 表头标题用QStringList来表示
  headerText << "日期"
             << "模式"
             << "用时（s）";

  // 表头各列的文字标题由一个 QStringList 对象 headerText
  // 初始化存储，如果只是设置行表头各列的标题，不设置样式，使用下面一行
  // ui->tableWidget->setHorizontalHeaderLabels(headerText);

  ui->tableWidget->setColumnCount(headerText.count());      // 列数设置为与 headerText的行数相等
  for (int i = 0; i < ui->tableWidget->columnCount(); i++)  // 列编号从0开始
  {
    // 新建一个QTableWidgetItem，headerText.at(i)获取headerText的i行字符串
    headerItem = new QTableWidgetItem(headerText.at(i));
    QFont font = headerItem->font();                          // 获取原有字体设置
    font.setBold(true);                                       // 设置为粗体
    font.setPointSize(12);                                    // 字体大小
    headerItem->setForeground(Qt::black);                     // 字体颜色
    headerItem->setFont(font);                                // 设置字体
    ui->tableWidget->setHorizontalHeaderItem(i, headerItem);  // 设置表头单元格的Item
  }
}
void RecordWidget::CreateRowItem(int row, const QDateTime& date, const QString& mode, const QString& time) {
  QTableWidgetItem* item;
  uint StudID = 201605000;  // 学号基数
  // 日期
  item = new QTableWidgetItem(date.toString("yyyy-MM-dd hh:mm:ss.zzz"), TABLE_ITEM_TYPE::DATE);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 文本对齐格式
  // row,col,item
  ui->tableWidget->setItem(row, TABLE_ITEM_TYPE::DATE, item);

  // 模式
  item = new QTableWidgetItem(mode, TABLE_ITEM_TYPE::MODE);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableWidget->setItem(row, TABLE_ITEM_TYPE::MODE, item);

  // 用时
  item = new QTableWidgetItem(time, TABLE_ITEM_TYPE::TIME);
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableWidget->setItem(row, TABLE_ITEM_TYPE::TIME, item);
}
void RecordWidget::AppendRowItem(const QDateTime& date, const QString& mode, const QString& time) {
  // 插入一行，但不会自动为单元格创建item
  ui->tableWidget->insertRow(mRowCount);
  // 为某一行创建items
  CreateRowItem(mRowCount, date, mode, time);
  mRowCount++;
}
void RecordWidget::ShowDBDataInTable() {
  LeveldbPimpl db;
  auto dataList = db.GetAllData();

  for (auto& it : dataList) {
    nlohmann::json json = nlohmann::json::parse(it);
    auto date = json.at("data_time").get<std::string>();
    int mode = json["mode"];
    auto time = json.at("time");

    fmt::print("date:{} mode:{} time:{}\n", date, mode, time);

    AppendRowItem(QDateTime::fromString(QString::fromStdString(date), "yyyy-MM-dd hh:mm:ss.zzz"), QString::number(mode),
                  QString::fromStdString(time));
  }
}
