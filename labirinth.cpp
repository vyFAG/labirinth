#include "labirinth.h"
#include "ui_labirinth.h"
#include <QPainter>
#include <random>
#include <QDebug>

Labirinth::Labirinth(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Labirinth)
{
    this->setFixedSize(400, 400);
    
    ui->setupUi(this);
    
    labirinth.resize(height_cells);
    
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,3);
    
    for (int h = 0; h < height_cells; h++) {
        labirinth[h].resize(width_cells);
        for (int w = 0; w < width_cells; w++) {
            labirinth[h][w].resize(1);
            
            for(int i = 0; i < 1; i++) {
                
                labirinth[h][w][i] = dist(gen);
            }
            
            qDebug() << labirinth[h][w];
        }
    }
}

Labirinth::~Labirinth()
{
    delete ui;
}

void Labirinth::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    
    for (int h = 0; h < height_cells; h++) {
        for (int w = 0; w < width_cells; w++) {
            painter.setBrush(QBrush(Qt::black));
            
            for(int i = 0; i < 1; i++) {
                switch(labirinth[h][w][i]) {
                case 0:
                    painter.drawLine(w * cell_width, h * cell_width, (w + 1) * cell_width, h * cell_width);
                    break;
                case 1:
                    painter.drawLine((w + 1) * cell_width, h * cell_width, (w + 1) * cell_width, (h + 1) * cell_width);
                    break;
                case 2:
                    painter.drawLine(w * cell_width, (h + 1) * cell_width, (w + 1) * cell_width, (h + 1) * cell_width);
                    break;
                case 3:
                    painter.drawLine(w * cell_width, h * cell_width, w * cell_width, (h + 1) * cell_width);
                    break;
                }
            }
        }
    }
}
