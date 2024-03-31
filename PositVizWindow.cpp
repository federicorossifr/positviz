//
// Created by Federico Rossi on 31/03/24.
//


#include "PositVizWindow.h"
#include <iostream>
PositVizWindow::PositVizWindow(QWidget* parent): QWidget(parent) {
    this->setWindowTitle("PositViz");
    auto* gl = new QGridLayout;
    gl->addWidget(createPositConfigurationBox(),0,0);
    gl->addWidget(createDecimalInputBox(),0,1);
    gl->addWidget(createPositOutputBox(),1,0,1,2);

    this->setLayout(gl);
    this->resize(640,320);
}

QGroupBox *PositVizWindow::createPositConfigurationBox() {
    auto *gb = new QGroupBox(tr("Posit configuration"));

    auto* nbitsSb = new QSpinBox();
    nbitsSb->setValue(8);
    auto* expSb = new QSpinBox();
    expSb->setValue(2);

    auto* withNaN = new QCheckBox();
    withNaN->setCheckState(Qt::CheckState(0));
    auto* withInf = new QCheckBox();
    withInf->setCheckState(Qt::CheckState(2));

    auto* nbitsLabel = new QLabel("Number of bits:");
    auto* expLabel = new QLabel("Maximum exponent bits:");
    auto* nanLabel = new QLabel("With NaN");
    auto* infLabel = new QLabel("With Inf");

    auto* withNanInfHbox = new QHBoxLayout();
    withNanInfHbox->addWidget(nanLabel);
    withNanInfHbox->addWidget(withNaN);
    withNanInfHbox->addWidget(infLabel);
    withNanInfHbox->addWidget(withInf);

    auto* applyButton = new QPushButton("Apply");

    auto *vb = new QVBoxLayout;
    vb->addWidget(nbitsLabel);
    vb->addWidget(nbitsSb);
    vb->addWidget(expLabel);
    vb->addWidget(expSb);
    vb->addLayout(withNanInfHbox);
    vb->addWidget(applyButton);
    gb->setLayout(vb);

    return gb;
}

QGroupBox *PositVizWindow::createDecimalInputBox() {
    auto *gb = new QGroupBox(tr("Decimal value input"));

    auto *decimalValueInput = new QLineEdit();
    _decimalValueInputField = decimalValueInput;
    decimalValueInput->setValidator(new QDoubleValidator(this));
    auto *decimalValueLabel = new QLabel("Decimal value: ");

    auto *hexValueInput = new QLineEdit();
    _positHexValueInputField = hexValueInput;
    auto *hexValueLabel = new QLabel("Posit hex value: ");
    const QString hexRegStr{"0[xX][0-9a-fA-F]+"};
    const QRegularExpression hexReg(hexRegStr);
    const QValidator *validator = new QRegularExpressionValidator(hexReg, this);
    hexValueInput->setValidator(validator);


    auto *intValueInput = new QLineEdit();
    _positIntValueInputField = intValueInput;
    intValueInput->setValidator(new QIntValidator(this));
    auto *intValueLabel = new QLabel("Posit int value: ");
    connect(_positIntValueInputField, &QLineEdit::textChanged, this, [&]() -> bool {
        auto newIntVal = _positIntValueInputField->text().toLong();
        _positHexValueInputField->setText("0x"+QString::number(newIntVal,16));
        return true;
    });

    connect(_positHexValueInputField, &QLineEdit::textChanged, this, [&]() -> bool {
        auto newIntVal = _positHexValueInputField->text().toLong(nullptr, 16);
        _positIntValueInputField->setText(QString::number(newIntVal,10));
        return true;
    });

    connect(_decimalValueInputField, &QLineEdit::textChanged, this, [&]() -> bool {
        _positIntValueInputField->setEnabled(_decimalValueInputField->text().isEmpty());
        _positHexValueInputField->setEnabled(_decimalValueInputField->text().isEmpty());
        return true;
    });

    auto* applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::released, this, &PositVizWindow::visualizeOutput);
    auto *vb = new QVBoxLayout;

    vb->addWidget(decimalValueLabel);
    vb->addWidget(decimalValueInput);
    vb->addWidget(hexValueLabel);
    vb->addWidget(hexValueInput);
    vb->addWidget(intValueLabel);
    vb->addWidget(intValueInput);
    vb->addWidget(applyButton);
    gb->setLayout(vb);

    return gb;
}

QGroupBox *PositVizWindow::createPositOutputBox() {
    auto *gb = new QGroupBox(tr("Posit output"));

    auto* positIntValueLabel = new QLabel("Posit int value: ");
    auto* positHexValueLabel = new QLabel("Posit hex value: ");
    auto* positDecimalValue = new QLabel("Decimal value (posit rounded): ");

    auto* positIntValue = new QLineEdit("-");
    positIntValue->setEnabled(false);
    _positIntValueLabel = positIntValue;
    auto* positHexValue = new QLineEdit("-");
    positHexValue->setEnabled(false);
    _positHexValueLabel = positHexValue;
    auto* positDecimal = new QLineEdit("-");
    positDecimal->setEnabled(false);
    _positDecimalLabel = positDecimal;

    auto *vb = new QVBoxLayout;
    vb->addWidget(positIntValueLabel);
    vb->addWidget(positIntValue);
    vb->addWidget(positHexValueLabel);
    vb->addWidget(positHexValue);
    vb->addWidget(positDecimalValue);
    vb->addWidget(positDecimal);

    gb->setLayout(vb);

    return gb;
}

void PositVizWindow::visualizeOutput() {
    _positIntValueLabel->setText("-");
    _positHexValueLabel->setText("-");
    _positDecimalLabel->setText("-");

    if(_decimalValueInputField->text().isEmpty()) {
        auto pHexString = _positHexValueInputField->text();
        auto pHexVal = pHexString.toLong(nullptr, 16);
        _positIntValueLabel->setText(QString::number(pHexVal));
        _positHexValueLabel->setText(pHexString);

        // ToDo process proper Posit value
        auto decimalValue = positToDouble(pHexVal);
        _positDecimalLabel->setText(QString::number(decimalValue));

    } else {
        double decimalValue = _decimalValueInputField->text().toDouble();

        auto [repr, roundedVal] = doubleToPosit(decimalValue);
        _positDecimalLabel->setText(QString::number(roundedVal));
        _positIntValueLabel->setText(QString::number(repr));
        _positHexValueLabel->setText("0x"+QString::number(repr,16));
    }



}

double PositVizWindow::positToDouble(int signed_raw) {
    using pp = posit::Posit<int8_t, 8, 2, uint8_t , posit::PositSpec::WithInfs>;
    return double(pp::from_sraw(signed_raw));
}

std::pair<int, double> PositVizWindow::doubleToPosit(double val) {
    using pp = posit::Posit<int8_t, 8, 2, uint8_t , posit::PositSpec::WithInfs>;
    return {pp(val).v, double(pp(val))};
}
