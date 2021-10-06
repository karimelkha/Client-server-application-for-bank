
/*	EL-KHARROUBI 	LEFEBVRE						*
 *	EISE4											*
 *	Reseaux											*
 *	TP4												*
 *	accounts.h : Déclaration des fonctions sur      *
 *les comptes			                            */
#ifndef __ACCOUNTS__


// Retourne les chaînes d'opérations
char* getCmds(int i);
int getLastOperations (char *operationFile, char *id, char *accountId,
		       char **headerOnly);
int updateOperationFile (customerArray * custs, char *opF);
int updateAccountFile (customerArray * custs, char *aF);
void updateOperations (account * account);
void displayOperations (account * account);
void addOperation (account * act, char opCode, int sum);
int removeFromAccount (customerArray * custs, int customerIndex,
		       int accountIndex, signed int amount);
int addToAccount (customerArray * custs, int customerIndex, int accountIndex,
		  signed int amount);
void getBalance(customerArray custs,int customerIndex, int accountIndex,char ** toSend); 
#endif
