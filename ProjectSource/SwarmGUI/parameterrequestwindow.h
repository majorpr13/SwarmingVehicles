#ifndef PARAMETERREQUESTWINDOW_H
#define PARAMETERREQUESTWINDOW_H

#include <QVector>
#include <QString>
#include <QDialog>

#include "command_helper.h"

namespace Ui {
class parameterRequestWindow;
}

class parameterRequestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit parameterRequestWindow(QWidget *parent = 0);
    void setValues(const QVector<Command_Helper::defaultCMD_Structure> &textLabels);
    ~parameterRequestWindow();
signals:
    void closingWindowEmpty();
    void closingWindowFull(QVector<double> returnVector);
private slots:
    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::parameterRequestWindow *ui;
};

#endif // PARAMETERREQUESTWINDOW_H
