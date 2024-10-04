#include "Compte.h"

Compte::Compte() {}

Compte::Compte(int clientId, double solde, int codeSecret, string rib, int chequier) {
    this->clientId = clientId;
    this->solde = solde;
    this->codeSecret = codeSecret;
    this->rib = rib;
    this->chequier = chequier;
}

void Compte::afficherCompte() {
    cout << "Solde: " << solde << endl;
    cout << "Code Secret: " << codeSecret << endl;
    cout << "RIB: " << rib << endl;
    cout << "Chequier: " << chequier << endl;
}

void Compte ::virer(sql::Connection* con, int clientIdDest, double montant) {
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Comptes SET solde = solde - ? WHERE clientId = ?");
    pstmt->setDouble(1, montant);
    pstmt->setInt(2, clientId);
    pstmt->executeUpdate();

    pstmt = con->prepareStatement("UPDATE Comptes SET solde = solde + ? WHERE clientId = ?");
    pstmt->setDouble(1, montant);
    pstmt->setInt(2, clientIdDest);
    pstmt->executeUpdate();

    cout << "Virement effectué avec succès !" << endl;
}

void Compte::debiter(sql::Connection* con, double montant) {
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Comptes SET solde = solde - ? WHERE clientId = ?");
    pstmt->setDouble(1, montant);
    pstmt->setInt(2, clientId);
    pstmt->executeUpdate();

    cout << "Débit effectué avec succès !" << endl;
}

void Compte::crediter(sql::Connection* con, double montant) {
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Comptes SET solde = solde + ? WHERE clientId = ?");
    pstmt->setDouble(1, montant);
    pstmt->setInt(2, clientId);
    pstmt->executeUpdate();

    cout << "Crédit effectué avec succès !" << endl;
}