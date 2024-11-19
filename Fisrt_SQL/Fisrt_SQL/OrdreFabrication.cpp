#include "OrdreFabrication.h"
#define EXIT_SUCCESS
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

using namespace std;

COrdreFabrication::COrdreFabrication()
	: m_reference(""), m_quantite(0.0), m_etat('X'), m_heureFin(""), m_preparateur(CPersonnel()), m_formule(CFormule())
{}

COrdreFabrication::COrdreFabrication(std::string reference, CFormule formule, double quantite,
	Etat etat, std::string heureFin, CPersonnel preparateur)
	: m_reference(reference), m_formule(formule), m_quantite(quantite),
	m_etat(etat), m_heureFin(heureFin), m_preparateur(preparateur)
{}

void COrdreFabrication::setReference(std::string reference)
{
	m_reference = reference;
}

void COrdreFabrication::setFormule(CFormule formule)
{
	m_formule = formule;
}

void COrdreFabrication::setQuantite(double quantite)
{
	m_quantite = quantite;
}

void COrdreFabrication::setEtat(Etat etat)
{
	switch (etat)
	{
	case COrdreFabrication::X: m_etat = 'X';
		break;
	case COrdreFabrication::E: m_etat = 'E';
		break;
	case COrdreFabrication::T: m_etat = 'T';
		break;
	}
}

void COrdreFabrication::setHeureFin(std::string heureFin)
{
	m_heureFin = heureFin;
}

void COrdreFabrication::setPreparateur(CPersonnel preparateur)
{
	m_preparateur = preparateur;
}

std::string COrdreFabrication::getReference() const
{
	return m_reference;
}

CFormule COrdreFabrication::getFormule() const
{
	return m_formule;
}

double COrdreFabrication::getQuantite() const
{
	return m_quantite;
}

char COrdreFabrication::getEtat() const
{
	return m_etat;
}

std::string COrdreFabrication::getHeureFin() const
{
	return m_heureFin;
}

CPersonnel COrdreFabrication::getPreparateur() const
{
	return m_preparateur;
}

std::string COrdreFabrication::toString() const
{
	return "Reference : " + m_reference + "\nFormule : " + m_formule.toString() + "\nQuantite : " + to_string(m_quantite) + "\nEtat : " + m_etat + "\nHeure de fin : " + m_heureFin + "\nOperateur : " + m_preparateur.toString();
}



