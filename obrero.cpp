#include "obrero.h"

obrero::obrero(QObject *parent)
    : QObject(parent)
{

}
obrero::obrero(const QString &nombre, int horas, TipoJornada jornada) : m_nombre(nombre),
    m_horas(horas),
    m_jornada(jornada)
{
    m_salarioBruto = 0;
    m_salarioNeto = 0;
    m_descuento = 0;
}
const QString &obrero::nombre() const
{
    return m_nombre;
}

void obrero::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

int obrero::horas() const
{
    return m_horas;
}

void obrero::setHoras(int newHoras)
{
    m_horas = newHoras;
}

TipoJornada obrero::jornada() const
{
    return m_jornada;
}

void obrero::setJornada(TipoJornada newJornada)
{
    m_jornada = newJornada;
}

double obrero::salarioBruto() const
{
    return m_salarioBruto;
}

void obrero::setSalarioBruto(double newSalarioBruto)
{
    m_salarioBruto = newSalarioBruto;
}

double obrero::salarioNeto() const
{
    return m_salarioNeto;
}

void obrero::setSalarioNeto(double newSalarioNeto)
{
    m_salarioNeto = newSalarioNeto;
}

double obrero::descuento() const
{
    return m_descuento;
}

void obrero::setDescuento(double newDescuento)
{
    m_descuento = newDescuento;
}

QString obrero::toString()
{
    QString str = "";
    str.append(tr("Nombre: %1").arg(m_nombre) + "\n");
        str.append(tr("Jornada: %1").arg(jornada2String()) + "\n");
        str.append(tr("Horas: %1").arg(QString::number(m_horas)) + "\n");
        str.append(tr("Salario Bruto: $%1").arg(QString::number(m_salarioBruto)) + "\n");
        str.append(tr("Descuento: $%1").arg(QString::number(m_descuento)) + "\n");
        str.append(tr("Salario Neto: $%1").arg(QString::number(m_salarioNeto)) + "\n");

    return str;
}

QString obrero::jornada2String()
{
    switch (m_jornada) {
    case TipoJornada::Matutina:
        return tr("Matutina");
        break;
    case TipoJornada::Vespertina:
        return tr("Vespertina");
        break;
    case TipoJornada::Nocturna:
        return tr("Nocturna");
        break;
    default:
        return "";
    }
}
