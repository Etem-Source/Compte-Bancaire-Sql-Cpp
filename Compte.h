#ifndef COMPTE_H
#define COMPTE_H

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class Compte {
private:
    int clientId;
    double solde;
    int codeSecret;
    string rib;
    int chequier;

public:
    Compte();
    Compte(int clientId, double solde, int codeSecret, string rib, int chequier);
    void afficherCompte();
    void virer(sql::Connection* con, int clientIdDest, double montant);
    void debiter(sql::Connection* con, double montant);
    void crediter(sql::Connection* con, double montant);
    int getClientId() { return clientId; }
    void setClientId(int clientId) { this->clientId = clientId; }
    double getSolde() { return solde; }
    void setSolde(double solde) { this->solde = solde; }
    int getCodeSecret() { return codeSecret; }
    void setCodeSecret(int codeSecret) { this->codeSecret = codeSecret; }
    string getRib() { return rib; }
    void setRib(string rib) { this->rib = rib; }
    int getChequier() { return chequier; }
    void setChequier(int chequier) { this->chequier = chequier; }
};

#endif