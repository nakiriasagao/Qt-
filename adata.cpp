#include "adata.h"
#include "ui_adata.h"

#include <QLabel>
#include <QPushButton>

Adata::Adata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adata)
{
    ui->setupUi(this);

    QLabel * data_label = new QLabel(this);
    QPushButton * data_btn = new QPushButton(this);
    data_btn->resize(500,500);
}

Adata::~Adata()
{
    delete ui;
}
