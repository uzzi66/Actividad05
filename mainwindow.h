#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Neurona{
    private:
        int id;
        float voltaje;
        int posicion_x;
        int posicion_y;
        int red;
        int blue;
        int green;
    public:
        string print();
        void salvar(fstream& out);
        void cargar(fstream& in);
        Neurona(){};
        Neurona(int i,float v,int px,int py,int r,int b,int g);
};

class administrar{
    private:
        vector<Neurona> vect;
        int aux;
    public:
        administrar();
        void salvar(fstream& out);
        void cargar(fstream& in);
        void agregar_inicio(Neurona n);
        void agregar_final(Neurona n);
        string mostrar();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inicio_clicked();

    void on_final_2_clicked();

    void on_mostrar_clicked();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

private:
    Ui::MainWindow *ui;
    administrar admin;
};
#endif // MAINWINDOW_H
