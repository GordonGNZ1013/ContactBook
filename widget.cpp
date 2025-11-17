#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setupUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupUI()
{
    // 從UI檔案中取得元件引用
    tableWidget = ui->tableWidget;
    lineEdit_studentId = ui->lineEdit_studentId;
    lineEdit_class = ui->lineEdit_class;
    lineEdit_name = ui->lineEdit_name;
    lineEdit_phone = ui->lineEdit_phone;
    btn_add = ui->btn_add;
    btn_export = ui->btn_export;
    
    // 設定表格屬性
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // 連接信號和槽
    connect(btn_add, &QPushButton::clicked, this, &Widget::addContact);
    connect(btn_export, &QPushButton::clicked, this, &Widget::exportToTxt);
}

void Widget::addContact()
{
    // 檢查所有欄位是否都有填寫
    if (lineEdit_studentId->text().isEmpty() || 
        lineEdit_class->text().isEmpty() ||
        lineEdit_name->text().isEmpty() || 
        lineEdit_phone->text().isEmpty()) {
        
        QMessageBox::warning(this, "警告", "請填寫所有欄位！");
        return;
    }
    
    // 在表格中新增一列
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    
    // 將輸入的資料加入表格
    tableWidget->setItem(row, 0, new QTableWidgetItem(lineEdit_studentId->text()));
    tableWidget->setItem(row, 1, new QTableWidgetItem(lineEdit_class->text()));
    tableWidget->setItem(row, 2, new QTableWidgetItem(lineEdit_name->text()));
    tableWidget->setItem(row, 3, new QTableWidgetItem(lineEdit_phone->text()));
    
    // 清空輸入欄位
    clearInputFields();
    
    QMessageBox::information(this, "成功", "聯絡人新增成功！");
}

void Widget::exportToTxt()
{
    // 選擇檔案儲存位置
    QString fileName = QFileDialog::getSaveFileName(this, 
                                                   "匯出通訊錄", 
                                                   "contacts.txt", 
                                                   "Text files (*.txt)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "錯誤", "無法開啟檔案進行寫入！");
        return;
    }
    
    QTextStream out(&file);
    
    // 寫入表格資料 (用逗號分隔格式)
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QString studentId = tableWidget->item(row, 0) ? tableWidget->item(row, 0)->text() : "";
        QString className = tableWidget->item(row, 1) ? tableWidget->item(row, 1)->text() : "";
        QString name = tableWidget->item(row, 2) ? tableWidget->item(row, 2)->text() : "";
        QString phone = tableWidget->item(row, 3) ? tableWidget->item(row, 3)->text() : "";
        
        out << studentId << "," << className << "," << name << "," << phone << "," << "\n";
    }
    
    file.close();
    
    QMessageBox::information(this, "成功", QString("通訊錄已成功匯出到：\n%1").arg(fileName));
}

void Widget::clearInputFields()
{
    lineEdit_studentId->clear();
    lineEdit_class->clear();
    lineEdit_name->clear();
    lineEdit_phone->clear();
}
