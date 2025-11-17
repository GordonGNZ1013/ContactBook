#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void addContact();        // 新增聯絡人
    void exportToTxt();       // 匯出到txt檔案

private:
    Ui::Widget *ui;
    
    // UI元件
    QTableWidget *tableWidget;
    QLineEdit *lineEdit_studentId;
    QLineEdit *lineEdit_class;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_phone;
    QPushButton *btn_add;
    QPushButton *btn_export;
    
    void setupUI();           // 設定UI介面
    void clearInputFields();  // 清空輸入欄位
};
#endif // WIDGET_H
