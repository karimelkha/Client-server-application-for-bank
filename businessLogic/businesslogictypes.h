/*	EL-KHARROUBI 	LEFEBVRE						*
 *	EISE4											*
 *	Reseaux											*
 *	TP4												*
 *	businessLogicTypes.h : types représentant la    *
 *  logique métier                                  */
#ifndef __BUSINESS_LOGIC_TYPES__

/*  Une opération a 
    un montant,
    un type et une date*/
typedef struct
{
  long long amount;
  char type;
  char *date;
} operation;

/*Un compte a un Id, 
  un solde
  un nombre d'opération
  et des opérations*/
typedef struct
{
  char *accountId;
  long long balance;
  int nbOps;
  operation *ops;
} account;


/* Un client à un Id,
   un mot de passe,
   un nombre de compte 
   et des ids de compte*/
typedef struct
{
  char *id;
  char *pw;
  int nbAccount;
  account *accounts;
} customer;


typedef struct
{
  int nbCustomers;
  customer *c;
} customerArray;



#endif
