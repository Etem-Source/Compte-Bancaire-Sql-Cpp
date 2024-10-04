#include "Client.h"

Client::Client() {}

Client::Client(int id, string nom, string prenom, string numcin, int numTel, Compte compte) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->numcin = numcin;
    this->numTel = numTel;
    this->compte = compte;
}

void Client::afficherClient() {
    cout << "Nom: " << nom << endl;
    cout << "Prénom: " << prenom << endl;
    cout << "Num CIN: " << numcin << endl;
    cout << "Num Tel: " << numTel << endl;
    compte.afficherCompte();
}

void Client::modifierClient(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Clients SET nom = ?, prenom = ?, numcin = ?, numTel = ? WHERE id = ?");
    pstmt->setString(1, nom);
    pstmt->setString(2, prenom);
    pstmt->setString(3, numcin);
    pstmt->setInt(4, numTel);
    pstmt->setInt(5, id);
    pstmt->executeUpdate();

    cout << "Client modifié avec succès !" << endl;
}