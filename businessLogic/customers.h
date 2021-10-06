/*	EL-KHARROUBI 	LEFEBVRE						*
 *	EISE4											*
 *	Reseaux											*
 *	TP4												*
 *	customers.h : définition de fonction de         *
 *  manipulation des clients                        */
#ifndef __CUSTOMERS__
#include "businesslogictypes.h"



int getAccountIndex (customerArray * custs, int localId, char *pw);
int authenticate (customerArray * custs, char *id, char *pw);
// Fonction de gestions de la mémoire
int liberateCustomer (customer cus);
int liberateCustomerArray (customer * custs, int nbCustomers);
int getClientsAndAccountFrom (const char *clientFilename,
			      const char *accountFileName,
			      customerArray * custs);
void display (customerArray * custs);
#endif
