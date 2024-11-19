
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

#include <vector>
#include <string>

#define EXIT_SUCCESS
#include <iostream>

// Chemins à modifier éventuellement
#include "Personnel.h"
#include "Formule.h"
#include "OrdreFabrication.h"
#include "BdDPVC.h"

using namespace std;

CBdDPVC::CBdDPVC()
	: m_driver(nullptr), m_con(nullptr), m_stmt(nullptr), m_res(nullptr)
{}

CBdDPVC::~CBdDPVC()
{}


bool CBdDPVC::connecter()
{
    cout << endl;
    cout << "Premier test du connecteur C++ Mysql" << endl;


    try {


        m_driver = get_driver_instance();

        m_con = m_driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");

        m_con->setSchema("picarda_b");

        m_stmt = m_con->createStatement();

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;
	return true;
}

bool CBdDPVC::connecter(std::string serveur, std::string login, std::string password, std::string baseDeDonnee)
{
    cout << endl;
    cout << "Premier test du connecteur C++ Mysql" << endl;

    try {

        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        driver = get_driver_instance();

        con = driver->connect(serveur, login, password);

        con->setSchema(baseDeDonnee);

        stmt = con->createStatement();
    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }
    cout << endl;
	return true;
}

void CBdDPVC::deconnecter()
{
	delete m_res;
	delete m_stmt;
	delete m_con;

}

bool CBdDPVC::estUnOperateurAutorise(CPersonnel user)
{


    string login, passwd;

    cout << "Rentrez votre login" << endl;
    cin >> login;

    cout << "Rentrez votre password" << endl;
    cin >> passwd;

    string req = "SELECT * FROM personnel WHERE password = '" + passwd + "' AND login = '" + login + "'"
        ;

    m_res = m_stmt->executeQuery(req);

    while (m_res->next()) 
    {
        if (login == m_res->getString("login") && passwd == m_res->getString("password"))
        {
            return true;

        }
        else
		{
			return false;
		}

    }

}

std::vector<std::string> CBdDPVC::getListeReferencesOF()
{
    string requete = "SELECT * FROM ordrefabrication";
	vector<string> listeOF;

    m_res = m_stmt->executeQuery(requete);

    while (m_res->next())
    {
		listeOF.push_back(m_res->getString("id_OrdreFabrication"));	
    }
}

std::vector<std::string> CBdDPVC::getReferencesOFaTraiter()
{
    string requete = "SELECT * FROM ordrefabrication WHERE etat = 'X' ";
    vector<string> listeOF;

    m_res = m_stmt->executeQuery(requete);

    while (m_res->next())
    {

        listeOF.push_back(m_res->getString("reference"));
    }
	return listeOF;
}

std::vector<std::string> CBdDPVC::getTypesFormule()
{
	string requete = "SELECT * FROM formule";
	vector<string> listeFormules;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		listeFormules.push_back(m_res->getString("type"));
	}
}

COrdreFabrication CBdDPVC::getOrdreFabrication(std::string referenceOF)
{
	string requete = "SELECT * FROM ordrefabrication WHERE id_OrdreFabrication = '" + referenceOF + "'";
	COrdreFabrication of;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		of.setReference(m_res->getString("id_OrdreFabrication"));
		of.setFormule(makeFormule(m_res->getInt("id_Formule")));
		of.setQuantite(m_res->getDouble("quantite"));

		if (m_res->getString("etat") == "X")
		{
			of.setEtat(COrdreFabrication::Etat::X);
		}
		else if (m_res->getString("etat") == "E")
		{
			of.setEtat(COrdreFabrication::Etat::E);
		}
		else if (m_res->getString("etat") == "T")
		{
			of.setEtat(COrdreFabrication::Etat::T);
		}

		of.setHeureFin(m_res->getString("heureFin"));
		of.setPreparateur(makePersonnel(m_res->getInt("id_Personnel")));
	}
    return of;
}

CPersonnel CBdDPVC::getPersonnel(std::string loginP)
{
	string requete = "SELECT * FROM personnel WHERE login = '" + loginP + "'";
	CPersonnel personnel;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		personnel.setLogin(m_res->getString("login"));
		personnel.setPassword(m_res->getString("password"));

		if (m_res->getString("qualite") == "OPERATEUR")
		{
			personnel.setQualite(CPersonnel::Qualite::OPERATEUR);
		}
		else if (m_res->getString("qualite") == "PREPARATEUR")
		{
			personnel.setQualite(CPersonnel::Qualite::PREPARATEUR);
		}

	}
	return personnel;
}

bool CBdDPVC::majEtatEnCours(COrdreFabrication& of, CPersonnel operateur)
{
	string requete = "UPDATE ordrefabrication SET etat = 'E', qualite = '" + operateur.getQualite() + "' WHERE id_OrdreFabrication = '" + of.getReference() + "' ";
	return m_stmt->executeUpdate(requete);
}

CFormule CBdDPVC::makeFormule(int idF)
{
	string requete = "SELECT * FROM formule WHERE id_Formule = " + to_string(idF) + "'";
	CFormule formule;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		formule.setType(m_res->getString("type"));
		formule.setPvcBase(m_res->getDouble("pvcBase"));
		formule.setPlastifiant(m_res->getDouble("plastifiant"));
		formule.setLubrifiant(m_res->getDouble("lubrifiant"));
		formule.setDureeMalaxage(m_res->getUInt("dureeMalaxage"));
		formule.setDureeRefroidissement(m_res->getUInt("dureeRefroidissement"));

	}
	return formule;
}

CPersonnel CBdDPVC::makePersonnel(int idP)
{
	string requete = "SELECT * FROM personnel WHERE id_Personnel = " + to_string(idP) + "'";
	CPersonnel personnel;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		personnel.setLogin(m_res->getString("login"));
		personnel.setPassword(m_res->getString("password"));

		if (m_res->getString("qualite") == "OPERATEUR")
		{
			personnel.setQualite(CPersonnel::Qualite::OPERATEUR);
		}
		else if (m_res->getString("qualite") == "PREPARATEUR")
		{
			personnel.setQualite(CPersonnel::Qualite::PREPARATEUR);
		}

	}
	return personnel;
}

bool CBdDPVC::majHeureFin(COrdreFabrication& of)
{
	string requete = "UPDATE ordrefabrication SET heureFin = '" + of.getHeureFin() + "' WHERE id_OrdreFabrication = '" + of.getReference() + "' ";
	return m_stmt->executeUpdate(requete);
	
}

int CBdDPVC::getIdFormule(CFormule formule)
{
	string requete = "SELECT * FROM formule WHERE type = '" + formule.getType() + "' AND pvcBase = " + to_string(formule.getPvcBase()) + " AND plastifiant = " + to_string(formule.getPlastifiant()) + " AND lubrifiant = " + to_string(formule.getLubrifiant()) + " AND dureeMalaxage = " + to_string(formule.getDureeMalaxage()) + " AND dureeRefroidissement = " + to_string(formule.getDureeRefroidissement()) + "'";
	int idF;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		idF = m_res->getInt("id_Formule");
	}
	return idF;
}

int CBdDPVC::getIdPersonnel(CPersonnel personnel)
{
	string requete = "SELECT * FROM personnel WHERE login = '" + personnel.getLogin() + "' AND password = '" + personnel.getPassword() + "' AND qualite = '" + personnel.getQualite() + "'";
	int idP;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		idP = m_res->getInt("id_Personnel");
	}
	return idP;
}

int CBdDPVC::getIdOF(COrdreFabrication of)
{
	string requete = "SELECT * FROM ordrefabrication WHERE id_OrdreFabrication = '" + of.getReference() + "' AND id_Formule = " + to_string(getIdFormule(of.getFormule())) + " AND quantite = " + to_string(of.getQuantite()) + " AND etat = '" + of.getEtat() + "' AND heureFin = '" + of.getHeureFin() + "' AND id_Personnel = " + to_string(getIdPersonnel(of.getPreparateur())) + "";
	int idOF;

	m_res = m_stmt->executeQuery(requete);

	while (m_res->next())
	{
		idOF = m_res->getInt("id_OrdreFabrication");
	}
	return idOF;
}

bool CBdDPVC::estOperateur(string login, string passwd)
{


	string req = "SELECT * FROM personnel WHERE password = '" + passwd + "' AND login = '" + login + "'"
		;

	m_res = m_stmt->executeQuery(req);

	while (m_res->next())
	{
		if (login == m_res->getString("login") && passwd == m_res->getString("password"))
		{
			return true;

		}
		else
		{
			return false;
		}

	}
}

void CBdDPVC::getOFaTraiter()
{
	vector<string> listeOF;
	listeOF = getReferencesOFaTraiter();
	cout << listeOF.size() << endl;
	for (int i = 0; i < listeOF.size(); i++)
	{
		cout << listeOF.at(i) << endl;
	}


}
