/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <User.h>
#include <ProfileServices.h>
#include <SecurityFilter.h>
#include <InterestResource.h>
#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"
#include "api/UserResource.h"
#include "api/AuthResource.h"
#include "services/authentication/AuthenticationService.h"

int main() {
	LOG_INFO << "Testing conection to shared server.";
	SharedConnector sharedConnector = SharedConnector("http://tinder-shared.herokuapp.com");
	if(!sharedConnector.testConnection()) LOG_ERROR << "Error probando conexion con el shared server";
	else LOG_INFO << "CONNECTION [OK]";


	LOG_INFO << "Starting DB";
	DBConnector authenticationDB = DBConnector("/tmp/authentication/");
	if(!authenticationDB.isOk()) LOG_ERROR << ("Error abriendo la DB de autenticación.");

	DBConnector translationDB = DBConnector("/tmp/translation/");
	if(!authenticationDB.isOk()) LOG_ERROR << ("Error abriendo la DB de traducción.");

	LOG_INFO << "Starting WebServer";

	UserDAO userDAO(&sharedConnector);
	AuthenticationDAO authDAO (authenticationDB);
	TranslationDAO transDAO (translationDB);
	ProfileServices profileService(&userDAO, &transDAO);
	AuthenticationService authService(&authDAO, &profileService);

	SecurityFilter securityFilter(authService);
	securityFilter.excludeRegex("/auth");
	ApiDispatcher dispatcher(securityFilter);

	UserResource user(profileService);

	user.setup(dispatcher);

	AuthResource auth (&authService);
	auth.setup(dispatcher);
	InterestResource interestResource(profileService);
	interestResource.setup(dispatcher);


	WebServer ws(dispatcher);

	ws.start();
	return 0;

}
