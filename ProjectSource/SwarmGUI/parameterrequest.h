#ifndef PARAMETERREQUEST_H
#define PARAMETERREQUEST_H

#include <QVector>
#include <QString>
#include <QDialog>

#include "command_helper.h"

namespace Ui {
class parameterRequest;
}

class parameterRequest : public QDialog
{
    Q_OBJECT
    
public:
    explicit parameterRequest(QWidget *parent = 0);
    ~parameterRequest();
    
    void setValues(const QVector<Command_Helper::defaultCMD_Structure> &textLabels);

    QVector<double> returnVector;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_destroyed();

private:
    Ui::parameterRequest *ui;
};

#endif // PARAMETERREQUEST_H
