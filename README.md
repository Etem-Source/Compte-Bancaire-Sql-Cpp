# 💸 Compte Bancaire MySQL
Ce projet permet de gérer les clients associés a des comptes bancaires ou se connecter a un compte, on peut y effectuer les tâches suivantes : 
* S'authentifier Client
  * Afficher ses informations
  * Faire un virement
  * Faire un débit
  * Faire un crédit
    
* Afficher tout les clients + comptes
* Afficher un client + compte en particulier

Par défaut, le mot de passe pour l'admin est : `123456`

## 💡 Prérequis
* [G++ Compileur](https://sourceforge.net/projects/mingw/)
  * `sudo apt install g++`
* [VisualStudio Code](https://code.visualstudio.com/) ou autres IDE
* Libmysqlcppconn-dev
  * `sudo apt update`
  * `sudo apt install libmysqlcppconn-dev`

## 💡 Prérequis MySQL
* Avoir MySQL
* Télécharger MySQL-CompteBancaire.sql
* Importer la base de données dans votre serveur MySQL :
  * mysql -u username* -p db_name* < MySQL-CompteBancaire.sql
    
*username = votre nom d'utilisateur.
*db_name = le nom de la bdd où vous souhaitez l'importer.

* Changer les valeurs par vos propres valeurs :
  * sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
  * sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "user*", "pw*");
  * con->setSchema("DB*");
    
*user = votre nom d'utilisateur.
*pw = votre mot de passe.
*DB = le nom de votre BDD.
    
## 🛠️ Utilisation
Vous devez d'abord compiler les fichiers .cpp (Si vous n'avez pas le .exe) : 

`g++ -o main *.cpp -lmysqlcppconn`

Ensuite, vous devez exécuter main.exe : 

`./main`

## 📚 Interface / Exemple

Petite idée de l'interface.

* Menu Principal :
  
![image](https://github.com/user-attachments/assets/5df91f00-0777-45ac-9a8c-85dd52816ace)

* Menu Client :
  
![image](https://github.com/user-attachments/assets/75df8413-e33f-491d-b4a4-05f8d9c9748b)


## 📧 Crédits
* [Etem](https://github.com/Etem-Source)

Merci d'avoir pris le temps de lire tout ceci.
Vous avez le droit de republier, réutiliser tout ce projet uniquement si vous créditez mon nom GitHub.
