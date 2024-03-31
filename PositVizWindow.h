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

public:
    explicit PositVizWindow(QWidget* parent = nullptr);
private:
    QGroupBox *createPositConfigurationBox();
    QGroupBox *createDecimalInputBox();
    QGroupBox *createPositOutputBox();

    void visualizeOutput();

    std::pair<int, double> doubleToPosit(double val);

    double positToDouble(int signed_raw);
};


#endif //POSITVIZ_POSITVIZWINDOW_H
