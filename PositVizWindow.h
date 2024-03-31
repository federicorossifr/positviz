//
// Created by Federico Rossi on 31/03/24.
//

#ifndef POSITVIZ_POSITVIZWINDOW_H
#define POSITVIZ_POSITVIZWINDOW_H

#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <iostream>
#include <QComboBox>

#include <posit.h>
using namespace posit;

class PositVizWindow: public QWidget
{
    Q_OBJECT
    QLineEdit* _positHexValueInputField{};
    QLineEdit* _positIntValueInputField{};
    QLineEdit* _decimalValueInputField{};

    QLineEdit* _positIntValueLabel{};
    QLineEdit* _positHexValueLabel{};
    QLineEdit* _positDecimalLabel{};

    QSpinBox* _positNbits{};
    QSpinBox* _positEsBits{};

    QComboBox* _positConfigurationSelection{};


    const QString _positConfigurationsLabels[8] = {"p8e0","p8e1","p8e2","p8e3","p16e0","p16e1","p16e2","p16e3"};
    const std::pair<int,int> _positConfigurations[8] = {{8,0},{8,1},{8,2},{8,3},{16,0},{16,1},{16,2},{16,3}};

public:
    explicit PositVizWindow(QWidget* parent = nullptr);
private:
    QGroupBox *createPositConfigurationBox();
    QGroupBox *createDecimalInputBox();
    QGroupBox *createPositOutputBox();
    QGroupBox *createPositToolsBox();

    void visualizeOutput();

    std::pair<int, double> doubleToPosit(double val);
    std::pair<int, int> getCurrentPositConfiguration();
    double positToDouble(int signed_raw);
};

using p8e0 = posit::Posit<int8_t, 8, 0, uint8_t , posit::PositSpec::WithNan>;
using p8e1 = posit::Posit<int8_t, 8, 1, uint8_t , posit::PositSpec::WithNan>;
using p8e2 = posit::Posit<int8_t, 8, 2, uint8_t , posit::PositSpec::WithNan>;
using p8e3 = posit::Posit<int8_t, 8, 3, uint8_t , posit::PositSpec::WithNan>;
using p16e0 = posit::Posit<int16_t, 16, 0, uint16_t , posit::PositSpec::WithNan>;
using p16e1 = posit::Posit<int16_t, 16, 1, uint16_t , posit::PositSpec::WithNan>;
using p16e2 = posit::Posit<int16_t, 16, 2, uint16_t , posit::PositSpec::WithNan>;
using p16e3 = posit::Posit<int16_t, 16, 3, uint16_t , posit::PositSpec::WithNan>;

#endif //POSITVIZ_POSITVIZWINDOW_H
