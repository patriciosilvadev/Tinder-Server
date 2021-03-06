//
// Created by jonathan on 30/04/16.
//

#ifndef TINDER_SERVER_SECURITYDAO1_H
#define TINDER_SERVER_SECURITYDAO1_H


#include <list>
#include <DBConnector.h>
#include "../model/User.h"

class AuthenticationDAO {

public:
	/**
        * It checks if the username received is already in the db.
        *
        * @param username username to look for in the DB.
        */
	bool isUsernameTaken(string username);


	AuthenticationDAO(DBConnector &dbConnector);

	/**
         * Save or update user with his password.
         *
         * @param username to create.
         * @param password to set to the username.
         */
	void saveUser(string username, string password);

	/**
	 * Delete user
	 * @param username the username
	 */
	void deleteUser(string username);

	string getPassword(string user);
	DBConnector & dbConnector;
};


#endif //TINDER_SERVER_SECURITYDAO1_H
