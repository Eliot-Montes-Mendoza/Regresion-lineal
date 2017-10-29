#include "reglin.h"
#include "ui_reglin.h"
#include <QTableWidgetItem>
#include <QString>

RegLin::RegLin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegLin)
{
    ui->setupUi(this);
    connect(ui->inicia,SIGNAL(Clicked()),this,SLOT(ejecutar()));
    connect(ui->limpia,SIGNAL(Clicked()),this,SLOT(limpiar()));
    connect(ui->carga,SIGNAL(Clicked()),this,SLOT(cargar()));
    ui->inicia->setDisabled(true);
    ui->limpia->setDisabled(true);
    ui->carga->setDisabled(true);
}
void RegLin::cargar(){
    puntosn=0,xsum=0,ysum=0,xysum=0;
    for(i=0;i<8;i++){// This cycle saves data from table widget items to a matrix:
        QTableWidgetItem* posicionx=ui->Tablap->item(i,0);// Creates a temporal variable for save each item value from the first table column.
        QTableWidgetItem* posiciony=ui->Tablap->item(i,1);// Creates a temporal variable for save each item value from the secound table column.
        if((!posicionx)||(!posiciony)){// If the table widget item isn't null (empty), the cycle continues.
            continue;
        }
        Matrix[i][0]=posicionx->text().toDouble();// Saves the value from table item to a matrix position (for "x").
        xsum=xsum+Matrix[i][0];// "xsum" saves the "x" points summation.
        x2sum=x2sum+(Matrix[i][0]*Matrix[i][0]);// "x2sum saves the squared "x" points summation.
        Matrix[i][1]=posiciony->text().toDouble();// Saves the value from table item to a matrix position (for "y").
        ysum=ysum+Matrix[i][1];// "ysum" saves the "y" points summation.
        y2sum=y2sum+(Matrix[i][1]*Matrix[i][1]);// "y2sum saves the squared "y" points summation.
        xysum=xysum+(Matrix[i][0]*Matrix[i][1]);// "xysum" saves the x*y sumation.
        puntosn++;// Sums one to point counter.
    }
    if(puntosn<3){// If the user introduced less than 3 points:
        ui->Tablap->setDisabled(false);// The first table widget keeps activate, till the user adds at least 3 points.
    }
    else{// If the user added at least 3 points:
        ui->carga->setDisabled(true);//Disables the Load button.
        ui->inicia->setDisabled(false);// Enables the start button.
        ui->Tablap->setDisabled(true);// Disables the first table widget.
    }
    ui->limpia->setDisabled(false);// Enables the clear button.
}

void RegLin::ejecutar(){// This slot will run the method, when the Start button been clicked after data introduction.
    sr=0, a0=0, a1=0, sxy=0, r=0;// These five variables starts from zero.
    xprom=xsum/puntosn;// Calculates the "x points" average.
    yprom=ysum/puntosn;// Calculates the "y points" average.
    a1=((puntosn*xysum)-(xsum*ysum))/((puntosn*x2sum)-(xsum*xsum));// Calculates the dependent term for straight line equation.
    a0=yprom-(a1*xprom);// Calculates the independent term for straigh line equation.
    for(i=0;i<puntosn;i++){// This cycle saves dispersion results in a new matrix.
        rMatrix[i][0]=(Matrix[i][1]-yprom)*(Matrix[i][1]-yprom);// Calculates the dispersion between points for each position.
        rMatrix[i][1]=(Matrix[i][1]-a0-(a1*Matrix[i][0]))*(Matrix[i][1]-a0-(a1*Matrix[i][0]));// Calculates the dispersion between each point and the found straight line.
        sr=sr+rMatrix[i][1];// "sr" saves the dispersion point-straight line summation.
        ui->Tablat->setItem(i,0,new QTableWidgetItem(QString::number(rMatrix[i][0])));// Show each dispersion between points value in the respective table widget position.
        ui->Tablat->setItem(i,1,new QTableWidgetItem(QString::number(rMatrix[i][1])));// Show each dispersion point-straight line in the respective table widget position.
    }
    sxy=sqrt(sr/(puntosn-2));// Calculates the estimated standard error, and saves it on "sxy".
    // Calculates the linear correlation coefficient, and saves it on "r".
    r=((puntosn*xysum)-(xsum*ysum))/(sqrt((puntosn*x2sum)-(xsum*xsum))*sqrt((puntosn*y2sum)-(ysum*ysum)));
    QString temp1, temp2, temp3, temp4, temp5;// Creates temporal text variables.
    //Creates a text srting with the found values.
    temp1.append("La ecuacion de la recta es: \n y= ").append(temp2.setNum(a0)).append("+").append(temp3.setNum(a1)).append("x").append(temp4.append("\n El coeficiente de correlacion lineal (r)=").append(temp5.setNum(r)));
    ui->textores->setText(temp1);// Shows the found straight line equation and the linear correlation coefficient at text browser.
}
void RegLin::limpiar(){// This slot will clear all user interface fields, when the Clear button been clicked.
    // Clears both table widgets.
    ui->Tablap->clearContents();
    ui->Tablat->clearContents();
    ui->textores->clear();// Clears text browser.
    ui->inicia->setDisabled(true);// Disables the start button.
    ui->limpia->setDisabled(true);// Disables the clear button.
    ui->carga->setDisabled(false);// Enables the load button.
    ui->Tablap->setDisabled(false);// Enables the first table widget.
}

RegLin::~RegLin()
{
    delete ui;
}
