#include "salarios.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator traduccion;
        // Solicitando al usuario que seleccione un idioma
        QStringList idiomas;
        idiomas << "Ucraniano" << "Español";

    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                   "Idioma",
                                   "Seleccione un idioma",
                                   idiomas);
        // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
        if (idiomaSeleccionado == "Ucraniano"){
            traduccion.load(":/salarios_uk_UK.qm");
        }

        // Si es diferente de español, se instala la traducción en TODA la aplicación
        if (idiomaSeleccionado != "Español"){
            a.installTranslator(&traduccion);}

    Salarios w;
    w.show();
    return a.exec();
}
