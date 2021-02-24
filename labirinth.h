#ifndef LABIRINTH_H
#define LABIRINTH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Labirinth; }
QT_END_NAMESPACE

class Labirinth : public QWidget
{
    Q_OBJECT
    
public:
    Labirinth(QWidget *parent = nullptr);
    ~Labirinth();
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    Ui::Labirinth *ui;
    
    int height_cells = 100;
    int width_cells = 100;
    int cell_width = 400 / height_cells;
    
    QVector<QVector<QVector<int>>> labirinth;
};
#endif // LABIRINTH_H