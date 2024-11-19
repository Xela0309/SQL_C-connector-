#include "Formule.h"
#define EXIT_SUCCESS
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

using namespace std;


CFormule::CFormule()
	: m_type("SOUPLE"), m_pvcBase(0), m_plastifiant(0), m_lubrifiant(0), m_dureeMalaxage(0), m_dureeRefroidissement(0)
{
}

CFormule::CFormule(string type, double pvcBase, double plastifiant,
	double lubrifiant, unsigned short dureeMalaxage,
	unsigned short dureeRefroidissement)
	: m_type(type), m_pvcBase(pvcBase), m_plastifiant(plastifiant), m_lubrifiant(lubrifiant), m_dureeMalaxage(dureeMalaxage), m_dureeRefroidissement(dureeRefroidissement)	
{
}

void CFormule::setType(string type)
{
	m_type = type;
}

void CFormule::setPvcBase(double pvcBase)
{
	m_pvcBase = pvcBase;
}

void CFormule::setPlastifiant(double plastifiant)
{
	m_plastifiant = plastifiant;
}

void CFormule::setLubrifiant(double lubrifiant)
{
	m_lubrifiant = lubrifiant;
}

void CFormule::setDureeMalaxage(unsigned short dureeMalaxage)
{
	m_dureeMalaxage = dureeMalaxage;
}

void CFormule::setDureeRefroidissement(unsigned short dureeRefroidissement)
{
	m_dureeRefroidissement = dureeRefroidissement;
}

std::string CFormule::getType() const
{
	return m_type;
}

double CFormule::getPvcBase() const
{
	return m_pvcBase;
}

double CFormule::getPlastifiant() const
{
	return m_plastifiant;
}

double CFormule::getLubrifiant() const
{
	return m_lubrifiant;
}

unsigned short CFormule::getDureeMalaxage() const
{
	return m_dureeMalaxage;
}


unsigned short CFormule::getDureeRefroidissement() const
{
	return m_dureeRefroidissement;
}

std::string CFormule::toString() const
{
	std::string message = "\n\tType : " + m_type + "\n";
	message += "\tpvcBase : " + std::to_string(m_pvcBase) + "\n";
	message += "\tplastifiant : " + std::to_string(m_plastifiant) + "\n";
	message += "\tlubrifiant : " + std::to_string(m_lubrifiant) + "\n";
	message += "\tdureeMalaxage : " + std::to_string(m_dureeMalaxage) + "\n";
	message += "\tdureeRefroidissement : " + std::to_string(m_dureeRefroidissement) + "\n";

	return message;
}
