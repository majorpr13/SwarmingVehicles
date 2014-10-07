#include "parameterrequest.h"
#include "ui_parameterrequest.h"

parameterRequest::parameterRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parameterRequest)
{
    ui->setupUi(this);
}

parameterRequest::~parameterRequest()
{
    delete ui;
}

void parameterRequest::on_buttonBox_accepted()
{
    returnVector.insert(0 , ui->doubleSpinBox1->value());
    returnVector.insert(1 , ui->doubleSpinBox2->value());
    returnVector.insert(2 , ui->doubleSpinBox3->value());
    returnVector.insert(3 , ui->doubleSpinBox4->value());
    returnVector.insert(4 , ui->doubleSpinBox5->value());
    returnVector.insert(5 , ui->doubleSpinBox6->value());
    returnVector.insert(6 , ui->doubleSpinBox7->value());
}

void parameterRequest::setValues(const QVector<Command_Helper::defaultCMD_Structure> &textLabels)
{
    if(textLabels.size() == 7)
    {
        ui->label->setText(textLabels.at(0).parameterName);
        ui->label_2->setText(textLabels.at(1).parameterName);
        ui->label_3->setText(textLabels.at(2).parameterName);
        ui->label_4->setText(textLabels.at(3).parameterName);
        ui->label_5->setText(textLabels.at(4).parameterName);
        ui->label_6->setText(textLabels.at(5).parameterName);
        ui->label_7->setText(textLabels.at(6).parameterName);

        ui->doubleSpinBox1->setEnabled(textLabels.at(0).enabled);
        ui->doubleSpinBox2->setEnabled(textLabels.at(1).enabled);
        ui->doubleSpinBox3->setEnabled(textLabels.at(2).enabled);
        ui->doubleSpinBox4->setEnabled(textLabels.at(3).enabled);
        ui->doubleSpinBox5->setEnabled(textLabels.at(4).enabled);
        ui->doubleSpinBox6->setEnabled(textLabels.at(5).enabled);
        ui->doubleSpinBox7->setEnabled(textLabels.at(6).enabled);

        ui->doubleSpinBox1->setValue(textLabels.at(0).defaultValue);
        ui->doubleSpinBox2->setValue(textLabels.at(1).defaultValue);
        ui->doubleSpinBox3->setValue(textLabels.at(2).defaultValue);
        ui->doubleSpinBox4->setValue(textLabels.at(3).defaultValue);
        ui->doubleSpinBox5->setValue(textLabels.at(4).defaultValue);
        ui->doubleSpinBox6->setValue(textLabels.at(5).defaultValue);
        ui->doubleSpinBox7->setValue(textLabels.at(6).defaultValue);

    }
}

void parameterRequest::on_buttonBox_rejected()
{

}

void parameterRequest::on_buttonBox_destroyed()
{

}
