#include "Personnel.h"
#define EXIT_SUCCESS
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

using namespace std;

CPersonnel::CPersonnel()
	: m_login(""), m_password(""), m_qualite("OPERATEUR")
{
}

CPersonnel::CPersonnel(std::string login, std::string password, Qualite qualite)
	: m_login(login), m_password(password)

{
setLogin(login);
setPassword(password);
setQualite(qualite);
}



void CPersonnel::setLogin(std::string login)
{
	m_login = login;
}

void CPersonnel::setPassword(std::string password)
{
	m_password = password;
}

void CPersonnel::setQualite(Qualite qualite)
{
	switch (qualite)
	{
	case CPersonnel::OPERATEUR: m_qualite = "OPERATEUR";
		break;
	case CPersonnel::PREPARATEUR: m_qualite = "PREPARATEUR";
		break;
	}
}

std::string CPersonnel::getLogin() const
{
	return m_login;
}

std::string CPersonnel::getPassword() const
{
	return m_password;
}

std::string CPersonnel::getQualite() const
{
	return m_qualite;
}

std::string CPersonnel::toString() const
{
	std::string message = m_login;
	message += " " + m_password;
	message += " " + m_qualite;
	return message;
}

