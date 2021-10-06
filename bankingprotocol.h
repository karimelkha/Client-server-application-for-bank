/*	EL-KHARROUBI 	LEFEBVRE						*
 *	EISE4											*
 *	Reseaux											*
 *	TP4												*
 *	businessLogicTypes.h : définitions et macros    *
 *  pour le protocole                               */

#ifndef __BANKING_PROTOCOL__


// Nombre de requêtes implémentées
// par le protocole
#define NB_REQ 4
// Port pour le protocole
#define PORT 8080
// Taille de l'entête
#define HEADER_SIZE 1
//Les 2 1ers bits donnent la requête
#define OP_CODE(a) ((*a) & 0x03)
#define ADD 0
#define WITHDRAWAL 1
#define BALANCE 2
#define OPERATIONS 3

// 4 bits pour le code de réponse
#define REP_CODE(a) ((*a) & 0x3C)
#define KO 1<<2
#define OK 1<<3
#define RES_OPERATION 1<<4
#define RES_SOL 1<<5

//Séparateur de trame
#define SEPARATOR_STR ":"
#define SEPARATOR ':'


#define DATE_FORMAT_SZ 28
// Taille des trames 
#define SOLDE_SZ 10
#define RET_RES_OP_SZ 22

#define BUFFER_SIZE 512

#define AJ_STR "AJOUT"
#define RE_STR "RETRAIT"
#define SO_STR "SOLDE"
#define OP_STR "OPERATIONS"
#define RES_STR "RESULTATOPERATION"


#define WELCOME_CLIENT_MESSAGE "\nWelcome to your online bank!\n""You can type the following commands:\n\t""\n\t- AJOUT {id} {account_id} {password} {amount} :\n\t\t""Add {amount} to {accound_id}\n\t-"" RETRAIT {id} {account_id} {password} {amount} :\n\t\t""Withdraw {amount} from {accound_id}\n\t- SOLDE {id}"" {account_id} {password} :\n\t\tCheck the balance of {account_id}\n\t""- OPERATIONS {id} {account_id} {password} :\n\t\t""Print the last ten operations on {account_id}\n"

#define NB_OPERATIONS 10

#define LOCALHOST "127.0.0.1"

#endif
