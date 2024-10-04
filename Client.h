#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "Compte.h"

using namespace std;

class Client {
private:
    int id;
    string nom;
    string prenom;
    string numcin;
    int numTel;
    Compte compte;

public:
    Client();
    Client(int id, string nom, string prenom, string numcin, int numTel, Compte compte);
    void afficherClient();
    void modifierClient(sql::Connection* con);
    int getId() { return id; }
    void setId(int id) { this->id = id; }
    string getNom() { return nom; }
    void setNom(string nom) { this->nom = nom; }
    string getPrenom() { return prenom; }
    void setPrenom(string prenom) { this->prenom = prenom; }
    string getNumcin() { return numcin; }
    void setNumcin(string numcin) { this->numcin = numcin; }
    int getNumTel() { return numTel; }
    void setNumTel(int numTel) { this->numTel = numTel; }
    Compte getCompte() { return compte; }
    void setCompte(Compte compte) { this->compte = compte; }
};

#endif