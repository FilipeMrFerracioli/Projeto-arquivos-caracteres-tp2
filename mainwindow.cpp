#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEditInvertido->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    try {
        QString texto = "";

        std::ifstream arquivo;

        QString nomeDoArquivo = QFileDialog::getOpenFileName(this, "Abrir arquivo",
                                                             QDir::currentPath(), "Arquivos texto (*.csv *.txt)");

        if(nomeDoArquivo.isEmpty()) throw QString("Arquivo não selecionado.");

        arquivo.open(nomeDoArquivo.toStdString().c_str());

        if(!arquivo.is_open()) throw QString("Erro: arquivo não pode ser aberto.");

        std::string linha = "";

        while(!arquivo.eof()) {
            std::getline(arquivo, linha);

            texto += QString::fromStdString(linha);
            texto += "\n";
        }

        arquivo.close();

        ui->textEditOriginal->setText(texto);

        texto = minhaNamespace::Caractere::inverterCaractere(texto);

        ui->textEditInvertido->setText(texto);
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}


void MainWindow::on_actionSalvar_triggered()
{
    try{
        QString texto = ui->textEditOriginal->toPlainText(); // == .text lineEdit

        //        ui->textEditInvertido->setText(minhaNamespace::Caractere::inverterCaractere(texto));
        //        texto = minhaNamespace::Caractere::inverterCaractere(texto);

        if(texto.isEmpty()) throw QString("Arquivo vazio.");

        std::ofstream arquivo;

        QString nomeDoArquivo = QFileDialog::getSaveFileName(this, "Novo arquivo",
                                                             QDir::currentPath(), "Arquivos texto (*.csv *.txt)");

        if(nomeDoArquivo.isEmpty()) throw QString("Arquivo não selecionado.");

        arquivo.open(nomeDoArquivo.toStdString().c_str());

        if(!arquivo.is_open()) throw QString("Erro: arquivo não pode ser criado.");

        arquivo << texto.toStdString().c_str() << std::endl;

        arquivo.close();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

