#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_contolador = new Controlador();
    m_porGuardar = false;
}

Salarios::~Salarios()
{
    delete ui;
}
void Salarios::on_btnCalcular_clicked()
{
    calcular();
}
void Salarios::on_actionNuevo_triggered()
{
    // Limpiar widgets
    limpiar();
    // Limpiar el texto de los calculos
    ui->outCalculos->clear();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage(tr("Nuevos cálculos de salario."), 3000);
}
void Salarios::limpiar()
{
    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}
void Salarios::calcular()
{
    // Obtener datos de la GUI
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada = TipoJornada::Matutina;
    }else if (ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }
    // Validacion de datos
    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,tr("Advertencia"),tr("El nombre y/o el número de horas es incorrecto"));
        return;
    }

    // Establecer datos al controlador
    m_contolador->setDatos(nombre, horas, jornada);
    // Calcular salarios
    if (m_contolador->calcular()) {
    // Muestra los resultados
        ui->outCalculos->appendPlainText(m_contolador->getDatos());
        // hay datos por guardar
           m_porGuardar = true;
    } else {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("No se puede calcular el salario."));
    }
    // Limpiar widgets
    limpiar();
    // Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage(tr("Salario de %1").arg(nombre) + tr(" calculado."),5000);

}

void Salarios::salir()
{
    if (m_porGuardar){
          int respuesta = QMessageBox::warning(
                      this,tr("Salir"),
                      tr("¿Desea guardar el archivo?"),tr("Si"),tr("No"));
          if (respuesta == QMessageBox::AcceptRole){
               on_actionGuardar_triggered();
          }
      }

    this->close();
}

void Salarios::abrir()
{
    if (m_porGuardar){
          int respuesta = QMessageBox::warning(
                      this,tr("Abrir"),
                      tr("¿Desea guardar el archivo actual?"),tr("Si"),tr("No"));
          if (respuesta == QMessageBox::AcceptRole){
               on_actionGuardar_triggered();
          }
      }

    // Abrir archivo
        QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                             tr("Abrir archivo"),
                                                             QDir::home().absolutePath(),
                                                             "Archivos de salarios (*.txt)");

        // Crear un objeto QFile
        QFile archivo(nombreArchivo);
        // Abrirlo para lectura
        if(archivo.open(QFile::ReadOnly)){
            // Crear un 'stream' de texto
            QTextStream entrada(&archivo);
            // Leer todo el contenido del archivo
            QString datos = entrada.readAll();
            // Cargar el contenido al área de texto
            ui->outCalculos->clear();
            ui->outCalculos->setPlainText(datos);
            // Mostrar 5 segundo que todo fue bien
            ui->statusbar->showMessage(tr("Datos leidos desde %1").arg(nombreArchivo), 5000);
        }else {
            // Mensaje de error si no se puede abrir el archivo
            QMessageBox::warning(this,
                                 tr("Abrir datos"),
                                 tr("No se pudo abrir el archivo"));
        }
        // Cerrar el archivo
        archivo.close();
}

void Salarios::on_actionCalcular_triggered()
{
    calcular();
}

void Salarios::on_actionSalir_triggered()
{
    salir();
}
void Salarios::on_actionGuardar_triggered()
{
    // Abrir un cuadro de diálogo para seleccionar el path y archivo a guardar
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                   tr("Guardar calculos de salarios"),
                                                   QDir::home().absolutePath() + "/salarios.txt",
                                                   "Archivos de texto (*.txt)");
    // Crear un objeto File
    QFile archivo(nombreArchivo);
    // Tartar de abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // cRear un objeto 'stream' de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outCalculos->toPlainText();
        // Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage(tr("Datos guardados en: %1").arg(nombreArchivo), 5000);
        // Cerrar el archivo
        archivo.close();
        // bajar la bandera
        m_porGuardar = false;
    }else {
        // Mensaje de error
        QMessageBox::warning(this,
                             tr("Guardar archivo"),
                             tr("No se puede acceder al archivo para guardar los datos."));
    }
}

void Salarios::on_actionAcerca_de_triggered()
{
    // Crear un objeto del cuadro de diálogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    // Mostrar la venta en modo MODAL
    dialog->exec();
    // Luego de cerrar la ventana, se acceden a los datos de la misma
    qDebug() << dialog->valor();
}

void Salarios::on_actionAbrir_triggered()
{
    abrir();
}

