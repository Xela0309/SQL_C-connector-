#include "Head.h"
#include "Formule.h"
#include "BdDPVC.h"
#include "OrdreFabrication.h"
#include "Personnel.h"
#define EXIT_SUCCESS
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

using namespace std;

void test()
{
	CFormule formule;
	CPersonnel preparateur;
	COrdreFabrication ordreFabrication;
	
	cout << ordreFabrication.toString() << endl;

	formule.setType("SOUPLE");
	formule.setPvcBase(50);
	formule.setPlastifiant(10);
	formule.setLubrifiant(5);
	formule.setDureeMalaxage(10);
	formule.setDureeRefroidissement(5);

	preparateur.setLogin("login");
	preparateur.setPassword("password");
	preparateur.setQualite(CPersonnel::OPERATEUR);

	ordreFabrication.setReference("ref");
	ordreFabrication.setFormule(formule);
	ordreFabrication.setQuantite(100);
	ordreFabrication.setEtat(COrdreFabrication::E);
	ordreFabrication.setHeureFin("12:00");
	ordreFabrication.setPreparateur(preparateur);

	cout << ordreFabrication.toString() << endl;

	cout << "Test de la connexion à la base de données\n\n\n\n\n\n\n" << endl;

	CBdDPVC bd;

	if (bd.connecter())
	{
		cout << "Connexion réussie" << endl;
		bd.getOFaTraiter();
	}
	else
	{
		cout << "Connexion échouée" << endl;
	}

	



}