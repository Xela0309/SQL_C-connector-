#include "Head.h"
#define EXIT_SUCCESS
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/driver.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/exception.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/resultset.h"
#include "mysql-connector-c++-noinstall-1.1.9-win32/mysql-connector-c++-noinstall-1.1.9-win32/include/cppconn/statement.h"

using namespace std;


void Q1()
{
    cout << endl;
    cout << "Premier test du connecteur C++ Mysql" << endl;

    // La gestion d'erreur se fait proprement avec les exceptions
    // sinon retirer le try...catch

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Etape 1 : créer une connexion à la BDD
        driver = get_driver_instance();
        // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");

        // Etape 2 : connexion à la base choisie, ici olivier_db
        con->setSchema("picarda_b");

        // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
        stmt = con->createStatement();


		string requete = "SELECT * FROM personnel WHERE qualite = 'OPERATEUR'";

        res = stmt->executeQuery(requete);
        while (res->next()) {
            cout << "\t... login: ";
            // Acces par non du champ de la table : ici le champ 'login' que l'on recupère au format string
            cout << res->getString("login") << endl;
            cout << "\t... Mdp: ";
            // Acces à la donnée par son numéro de colonne, 3
            cout << res->getString(3) << endl;
        }
        

        // On nettoie tout avant de sortir : effacement des pointeurs
        // le pointeur sur le Driver sera effacé tout seul
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    // on sort en indiquant que tout c'est bien passé
    // return EXIT_SUCCESS;
}

void Q2()
{
    cout << endl;

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Etape 1 : créer une connexion à la BDD
        driver = get_driver_instance();
        // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");

        // Etape 2 : connexion à la base choisie, ici olivier_db
        con->setSchema("picarda_b");

        // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
        stmt = con->createStatement();


        string login,passwd;
        cout << "Rentrez votre login" << endl;
        cin >> login;

        cout << "Rentrez votre password" << endl;
        cin >> passwd;

        string requete = "SELECT * FROM personnel ";
        
        string requete2 = "SELECT * FROM personnel WHERE password = '" + passwd + "' AND login = '" + login + "'"
            ;

        res = stmt->executeQuery(requete2);

        while (res->next()) {
            /*
			if (login == res->getString("login") && passwd == res->getString("password"))
			{
				cout << "Vous êtes OPERATEUR" << endl;

			}
            */
            if (res->getString("qualite") == "OPERATEUR")
            {
                cout << "Vous êtes OPERATEUR" << endl;

            }
            else
			{
				cout << "Vous n'êtes pas OPERATEUR" << endl;
			}

        }

        
        // On nettoie tout avant de sortir : effacement des pointeurs
        // le pointeur sur le Driver sera effacé tout seul
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    // on sort en indiquant que tout c'est bien passé
    // return EXIT_SUCCESS;
}

void Q3()
{
    cout << endl;

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Etape 1 : créer une connexion à la BDD
        driver = get_driver_instance();
        // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");

        // Etape 2 : connexion à la base choisie, ici olivier_db
        con->setSchema("picarda_b");

        // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
        stmt = con->createStatement();


        string requete = "SELECT * FROM ordrefabrication WHERE etat = 'X'";

        res = stmt->executeQuery(requete);
        
        while (res->next()) 
        {
            cout << "\tid : ";
			cout << res->getString("id_OrdreFabrication") << endl;

        }


        // On nettoie tout avant de sortir : effacement des pointeurs
        // le pointeur sur le Driver sera effacé tout seul
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    // on sort en indiquant que tout c'est bien passé
    // return EXIT_SUCCESS;
}

void Q4()
{
    cout << endl;

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;
        driver = get_driver_instance();
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");
        con->setSchema("picarda_b");
        stmt = con->createStatement();



		cout << "Les formules non traité" << endl;

        
        string requete = "SELECT * FROM ordrefabrication o , formule f WHERE f.id_Formule = o.id_Formule AND o.etat = 'X' ";
        string demande;

        res = stmt->executeQuery(requete);
        

        while (res->next())
        {
			cout << "\t... Reference : ";
			cout << res->getString("reference") << endl;

        }

		cout << "Veuillez choisir la reference à calculer" << endl;
		cin >> demande;

        string requete2 = "SELECT * FROM ordrefabrication o , formule f WHERE f.id_Formule = o.id_Formule AND o.etat = 'X' AND o.reference = '" + demande + "'";

        res = stmt->executeQuery(requete2);
        double nbpvc = 0, nbplastifiant = 0, nblubrifiant = 0;

        while (res->next())
        {
            nbpvc = (res->getDouble("pvcBase") * res->getDouble("quantite")) / 100;
            nblubrifiant = (res->getDouble("lubrifiant") * res->getDouble("quantite")) / 100;
            nbplastifiant = (res->getDouble("plastifiant") * res->getDouble("quantite")) / 100;

            cout << "\t... id : ";
            cout << res->getString("id_OrdreFabrication") << endl;
            cout << "\t... PVC : ";
            cout << nbpvc << endl;
            cout << "\t... Lubrifiant : ";
            cout << nblubrifiant << endl;
            cout << "\t... Plastifiant : ";
            cout << nbplastifiant << endl;
        }



        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

}

void Q5()
{
    cout << endl;

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;
        driver = get_driver_instance();
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");
        con->setSchema("picarda_b");
        stmt = con->createStatement();

        string confirmation =
            "SELECT * FROM personnel WHERE qualite = 'OPERATEUR'";
        
		string login, passwd,idperso;
       


        double nbpvc = 0, nbplastifiant = 0, nblubrifiant = 0;
		bool ident = false;

		while (ident == false)
		{
			cout << "Rentrez votre login" << endl;
			cin >> login;

			cout << "Rentrez votre password" << endl;
			cin >> passwd;

			if (login == "exit" || passwd == "exit")
			{
				break;
			}

            res = stmt->executeQuery(confirmation);

            while (res->next())
            {
				if (login == res->getString("login") && passwd == res->getString("password"))
                {
					idperso = res->getString("id_Personnel");
					cout << "Vous etes OPERATEUR" << endl;
					ident = true;
					break;
				}


            }
			if (ident == false)
			{
				cout << "Vous n'etes pas OPERATEUR" << endl;
			}
        }

        string affichage = "SELECT * FROM ordrefabrication o , formule f WHERE f.id_Formule = o.id_Formule AND o.etat = 'X' ";
        string demande;

        res = stmt->executeQuery(affichage);


		if (res->rowsCount() != 0)
        {
            while (res->next())
            {
                cout << "\t... Reference : ";
                cout << res->getString("reference") << endl;

            }

            cout << "Veuillez choisir la reference à calculer" << endl;
            cin >> demande;


            string update = " Update ordrefabrication set etat = 'E' , id_Personnel = '" + idperso + "' WHERE etat = 'X' AND reference = '" + demande + "'";

            stmt->executeUpdate(update);



		}
        else
        {
			cout << "Il n'y a pas d'ordre de fabrication à traiter" << endl;
        }



        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

}

void Q6()
{
    cout << endl;

    try {
        // Les variables nécessaires à notre programme
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;
        driver = get_driver_instance();
        con = driver->connect("tcp://10.187.52.4:3306", "picarda", "picarda");
        con->setSchema("picarda_b");
        stmt = con->createStatement();

        string confirmation =
            "SELECT * FROM personnel WHERE qualite = 'OPERATEUR'";

        string login, passwd, idperso;



        double nbpvc = 0, nbplastifiant = 0, nblubrifiant = 0;
        bool ident = false;

        while (ident == false)
        {
            cout << "Rentrez votre login" << endl;
            cin >> login;

            cout << "Rentrez votre password" << endl;
            cin >> passwd;

            if (login == "exit" || passwd == "exit")
            {
                break;
            }

            res = stmt->executeQuery(confirmation);

            while (res->next())
            {
                if (login == res->getString("login") && passwd == res->getString("password"))
                {
                    idperso = res->getString("id_Personnel");
                    cout << "Vous etes OPERATEUR" << endl;
                    ident = true;
                    break;
                }


            }
            if (ident == false)
            {
                cout << "Vous n'etes pas OPERATEUR" << endl;
            }
        }

        string affichage = "SELECT * FROM ordrefabrication o , formule f WHERE f.id_Formule = o.id_Formule AND o.etat = 'E' ";
        string demande;

        res = stmt->executeQuery(affichage);


        if (res->rowsCount() != 0)
        {
            while (res->next())
            {
                cout << "\t... Reference : ";
                cout << res->getString("reference") << endl;

            }

            cout << "Veuillez choisir la reference à calculer" << endl;
            cin >> demande;


            string update = " Update ordrefabrication set etat = 'T' , heurefin = NOW() , id_Personnel = '" + idperso + "' WHERE etat = 'E' AND reference = '" + demande + "'";

            stmt->executeUpdate(update);


        }
        else
        {
            cout << "Il n'y a pas d'ordre de fabrication à traiter" << endl;
        }

        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        // Gestion des execeptions pour déboggage
        cout << "# ERR: " << e.what();
        cout << " (code erreur MySQL: " << e.getErrorCode();
        cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

}