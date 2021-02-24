#include "labirinth.h"
#include "ui_labirinth.h"
#include <QPainter>
#include <random>
#include <QDebug>

Labirinth::Labirinth(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Labirinth)
{
    this->setFixedSize(401, 401);
    
    ui->setupUi(this);
    
    vertical_barier.resize(height_cells - 1);
    horizontal_barier.resize(height_cells - 1);
    
    for(int h = 0; h < height_cells - 1; h++) {
        for(int w = 0; w < width_cells - 1; w++) {
            vertical_barier[h].resize(width_cells - 1);
            vertical_barier[h].fill(1);
            
            horizontal_barier[h].resize(width_cells - 1);
            horizontal_barier[h].fill(1);
        }
    }
    
    horizontal_barier[0].fill(0);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,1);
    
    int beg_index = 0;
    int counter = 0;
    
    for(int h = 1; h < height_cells; h++) {
        beg_index = 0;
        counter = 0;
        for(int w = 0; w < width_cells; w++) {
            if (dist(gen) == 1 || w < width_cells) {
                std::uniform_int_distribution<> rand_cell(beg_index, beg_index + counter);
                
                int random_cell = rand_cell(gen);
                
                vertical_barier[h - 1][random_cell] = 0;
                
                for (int i = beg_index; i < beg_index + counter - 1; i++) {
                    horizontal_barier[h][i] = 0;
                }
                
                if (w + 1 == width_cells) {
                    break;
                }
            }
            
            else {
                counter++;
            }
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
    
    painter.drawRect(0, 0, 400, 400);
    
    for (int h = 0; h < height_cells - 1; h++) {
        for (int w = 0; w < width_cells - 1; w++) {
            painter.setBrush(QBrush(Qt::black));
            if (h > 0) {
                if (horizontal_barier[h - 1][w] == 1) {
                    painter.drawLine(h * cell_width, w * cell_width, h * cell_width, (w + 1) * cell_width);
                }
            }
            
            if (w > 0) {
                if (vertical_barier[h][w - 1] == 1) {
                    painter.drawLine(h * cell_width, w * cell_width, (h + 1) * cell_width, w * cell_width);
                }
            }
        }
    }
}
