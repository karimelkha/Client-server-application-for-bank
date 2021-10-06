#ifndef __CUSTOMERS__
#define DEBUG_REP   "data/"
#define DEBUG_ACCOUNTF DEBUG_REP"accountFile"
#define DEBUG_CLIENTF DEBUG_REP"clientFile"
#define DEBUG_OPERATIONF DEBUG_REP"operationFile"
#define WELCOME_CLIENT_MESSAGE "\nWelcome to your online bank!\n""You can type the following commands:\n\t""\n\t- AJOUT {id} {account_id} {password} {amount} :\n\t\t""Add {amount} to {accound_id}\n\t-"" RETRAIT {id} {account_id} {password} {amount} :\n\t\t""Withdraw {amount} from {accound_id}\n\t- SOLDE {id}"" {account_id} {password} :\n\t\tCheck the balance of {account_id}\n\t""- OPERATIONS {id} {account_id} {password} :\n\t\t""Print the last ten operations on {account_id}\n"
#define NB_MAX_CO 10



#endif
