#ifndef REGLIN_H
#define REGLIN_H

#include <QMainWindow>

namespace Ui {
class RegLin;
}

class RegLin : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegLin(QWidget *parent = 0);
    ~RegLin();
    double Matrix[7][2];
    double rMatrix [7][2];
    double xsum,ysum,xysum,y2sum,x2sum;
    double xprom,yprom;
    double a0,a1;
    double errorE,sxy,sr,r;
    int puntosn;
    int i,j;
public slots:
    void ejecutar();
    void limpiar();
    void cargar();

private:
    Ui::RegLin *ui;
};

#endif // REGLIN_H
