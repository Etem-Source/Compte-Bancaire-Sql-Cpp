#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <string>
#include "Client.h"
#include "Compte.h"

using namespace std;

// Fonction pour importer les clients depuis la base de données
Client importClient(sql::Connection* con, int clientId) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Clients WHERE id = ?");
    pstmt->setInt(1, clientId);
    sql::ResultSet* res = pstmt->executeQuery();

    Client client;

    if (res->next()) {
        client.setId(res->getInt("id"));
        client.setNom(res->getString("nom"));
        client.setPrenom(res->getString("prenom"));
        client.setNumcin(res->getString("numcin"));
        client.setNumTel(res->getInt("numTel"));

        sql::PreparedStatement* pstmtCompte = con->prepareStatement("SELECT * FROM Comptes WHERE clientId = ?");
        pstmtCompte->setInt(1, clientId);
        sql::ResultSet* resCompte = pstmtCompte->executeQuery();

        if (resCompte->next()) {
            Compte compte(resCompte->getInt("clientId"), resCompte->getDouble("solde"), resCompte->getInt("codeSecret"), resCompte->getString("rib"), resCompte->getInt("chequier"));
            client.setCompte(compte);
        }

        delete pstmtCompte;
        delete resCompte;
    }

    delete pstmt;
    delete res;

    return client;
}

// Fonction pour afficher le profil d'un client
void afficherProfil(sql::Connection* con, Client client) {
    cout << "> Profil de " << client.getNom() << " " << client.getPrenom() << endl;
    cout << "Nom : " << client.getNom() << endl;
    cout << "Prénom : " << client.getPrenom() << endl;
    cout << "Num CIN : " << client.getNumcin() << endl;
    cout << "Num Tel : " << client.getNumTel() << endl;
    cout << "Solde : " << client.getCompte().getSolde() << endl;
    cout << "Code Secret : " << client.getCompte().getCodeSecret() << endl;
    cout << "RIB : " << client.getCompte().getRib() << endl;
    cout << "Chequier : " << client.getCompte().getChequier() << endl;
}

// Fonction pour afficher tous les clients
void afficherTousLesClients(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Clients");
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "> Client " << res->getInt("id") << endl;
        cout << "Nom : " << res->getString("nom") << endl;
        cout << "Prénom : " << res->getString("prenom") << endl;
        cout << "Num CIN : " << res->getString("numcin") << endl;
        cout << "Num Tel : " << res->getInt("numTel") << endl;
        cout << endl;
    }

    sql::PreparedStatement* pstmt2 = con->prepareStatement("SELECT * FROM Comptes");
    sql::ResultSet* res2 = pstmt2->executeQuery();

    while (res2->next()) {
        cout << "> Compte : " << res2->getInt("clientId") << endl;
        cout << "Solde : " << res2->getDouble("solde") << endl;
        cout << "Code Secret : " << res2->getInt("codeSecret") << endl;
        cout << "RIB : " << res2->getString("rib") << endl;
        cout << "Chequier : " << res2->getInt("chequier") << endl;
        cout << endl;
    }

    delete pstmt;
    delete res;
    delete pstmt2;
    delete res2;
}

void afficherClient(sql::Connection* con, int clientId) {
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    pstmt = con->prepareStatement("SELECT * FROM Clients WHERE id = ?");
    pstmt->setInt(1, clientId);
    res = pstmt->executeQuery();

    if (res->next()) {
        int id = res->getInt(1); // Column index starts from 1
        string nom = res->getString(2);
        string prenom = res->getString(3);
        string numCIN = res->getString(4);

        cout << "> Client " << id << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prénom : " << prenom << endl;
        cout << "Num CIN : " << numCIN << endl;
    } else {
        cout << "Client non trouvé" << endl;
    }

    delete pstmt;
    delete res;
}

int main() {
    sql::Driver* driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "etem", "etemsql94");

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE Banque");

    int choix;
    do {
        cout << "> Menu principal" << endl;
        cout << "1. Se connecter" << endl;
        cout << "2. Afficher tous les clients" << endl;
        cout << "3. Afficher un client" << endl;
        cout << "0. Quitter" << endl;
        cin >> choix;

        switch (choix) {
            case 1: {
                int clientId;
                cout << "Entrez votre ID client : ";
                cin >> clientId;

                Client client = importClient(con, clientId);

                if (client.getId() != 0) {
                    int codeSecret;
                    cout << "Entrez votre code secret : ";
                    cin >> codeSecret;

                    if (codeSecret == client.getCompte().getCodeSecret()) {
                        int choixClient;
                        do {
                            cout << "> Bienvenue " << client.getNom() << " " << client.getPrenom() << endl;
                            cout << "- Solde : " << client.getCompte().getSolde() << endl;
                            cout << "1. Effectuer un virement" << endl;
                            cout << "2. Effectuer un débit" << endl;
                            cout << "3. Effectuer un crédit" << endl;
                            cout << "4. Afficher mon profil" << endl;
                            cout << "0. Revenir au menu principal" << endl;
                            cin >> choixClient;

                            switch (choixClient) {
                                case 1: {
                                    int clientIdDest;
                                    double montant;
                                    cout << "Entrez l'ID du client destinataire : ";
                                    cin >> clientIdDest;
                                    cout << "Entrez le montant à virer : ";
                                    cin >> montant;

                                    Client clientDest = importClient(con, clientIdDest);

                                    if (clientDest.getId() != 0) {
                                        client.getCompte().virer(con, clientIdDest, montant);
                                        client.getCompte().setSolde(client.getCompte().getSolde() - montant); // Actualiser le solde
                                        cout << "Virement effectué avec succès !" << endl;
                                    } else {
                                        cout << "Client destinataire non trouvé" << endl;
                                    }
                                    break;
                                }
                                case 2: {
                                    double montant;
                                    cout << "Entrez le montant à débiter : ";
                                    cin >> montant;

                                    client.getCompte().debiter(con, montant);
                                    client.getCompte().setSolde(client.getCompte().getSolde() - montant); // Actualiser le solde
                                    cout << "Débit effectué avec succès !" << endl;
                                    break;
                                }
                                case 3: {
                                    double montant;
                                    cout << "Entrez le montant à créditer : ";
                                    cin >> montant;

                                    client.getCompte().crediter(con, montant);
                                    client.getCompte().setSolde(client.getCompte().getSolde() + montant); // Actualiser le solde
                                    cout << "Crédit effectué avec succès !" << endl;
                                    break;
                                }
                                case 4: {
                                    afficherProfil(con, client);
                                    break;
                                }
                            }
                            // Actualiser le solde en temps réel
                            client = importClient(con, clientId);
                        } while (choixClient != 0);
                    } else {
                        cout << "Code secret incorrect" << endl;
                    }
                } else {
                    cout << "Client non trouvé" << endl;
                }
                break;
            }
            case 2: {
                afficherTousLesClients(con);
                break;
            }
            case 3: {
                int clientId;
                cout << "Entrez l'ID du client à afficher : ";
                cin >> clientId;

                afficherClient(con, clientId);
                break;
            }
        }
    } while (choix != 0);

    delete stmt;
    delete con;

    return 0;
}