#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <qfiledialog.h>
#include<sstream>
#include <fstream>
using namespace std;

Neurona::Neurona(int i,float v,int px,int py,int r,int b,int g){
    id=i;
    voltaje=v;
    posicion_x=px;
    posicion_y=py;
    red=r;
    blue=b;
    green=g;
}

string Neurona::print(){
    string s;
    ostringstream o;
    o <<"ID:"<<id<<endl
    <<"Voltaje:"<<voltaje<<endl
    <<"Posicion x:"<<posicion_x<<endl
    <<"Posicion y:"<<posicion_y<<endl
    <<"Rojo:"<<red<<endl
    <<"Azul:"<<blue<<endl
    <<"Verde:"<<green<<endl<<endl;
    s = o.str();
    return s;
}

void Neurona::salvar(fstream& out){
    out<<id<<endl;
    out<<voltaje<<endl;
    out<<posicion_x<<endl;
    out<<posicion_y<<endl;
    out<<red<<endl;
    out<<blue<<endl;
    out<<green<<endl;
}

void Neurona::cargar(fstream& in){
    in>>id;
    in>>voltaje;
    in>>posicion_x;
    in>>posicion_y;
    in>>red;
    in>>blue;
    in>>green;
}

administrar::administrar(){
    aux=0;
}

void administrar::agregar_inicio(Neurona n){
    vect.insert(vect.begin(), n);
    aux++;
}

void administrar::salvar(fstream& out){
    out<<aux<<endl;
    for(int i=0;i<aux;i++){
        vect[i].salvar(out);
    }
}

void administrar::cargar(fstream& in){
    in>>aux;
    for(int i=0;i<aux;i++){
        Neurona n;
        n.cargar(in);
        vect.insert(vect.end(), n);
    }
}

void administrar::agregar_final(Neurona n){
    vect.insert(vect.end(), n);
    aux++;
}

string administrar::mostrar(){
    string s;
    ostringstream o;
    for(int i=0;i<aux;i++){
        o<<vect[i].print();
    }
    s = o.str();
    return s;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inicio_clicked()
{
    int id = ui->id->value();
    float volt = ui->volt->value();
    int posx = ui->posx->value();
    int posy = ui->posy->value();
    int red = ui->red->value();
    int blue = ui->blue->value();
    int green = ui->green->value();
    Neurona n(id,volt,posx,posy,red,blue,green);
    admin.agregar_inicio(n);
}


void MainWindow::on_final_2_clicked()
{
    int id = ui->id->value();
    float volt = ui->volt->value();
    int posx = ui->posx->value();
    int posy = ui->posy->value();
    int red = ui->red->value();
    int blue = ui->blue->value();
    int green = ui->green->value();
    Neurona n(id,volt,posx,posy,red,blue,green);
    admin.agregar_final(n);
}


void MainWindow::on_mostrar_clicked()
{
    string s = admin.mostrar();
    ui->pantalla->setPlainText(QString::fromStdString (s));
}


void MainWindow::on_actionAbrir_triggered()
{
    QString Filenameopen = QFileDialog::getOpenFileName(this,"Abrir archivo",".","archivo (*.txt)") ;
    string file=Filenameopen.toStdString();
    fstream entrada(file,ios_base::in);
    admin.cargar(entrada);
}


void MainWindow::on_actionGuardar_triggered()
{
    QString Filenamesave = QFileDialog::getSaveFileName(this,"Guardar archivo",".","archivo (*.txt)");
    string file=Filenamesave.toStdString();
    fstream salida(file,ios_base::out);
    admin.salvar(salida);
}
