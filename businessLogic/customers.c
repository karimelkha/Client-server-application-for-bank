/*	EL-KHARROUBI 	LEFEBVRE						              *
 *	EISE4											                      *
 *	Reseaux											                    *
 *	TP4												                      *
 *	customers.c : définitions du traitement des     *
 *  clients                                         */
#include "customers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../bankingprotocol.h"


int
getAccountIndex (customerArray * custs, int customerIndex, char *accountId)
{
  int i;

  for (i = 0; i < custs->c[customerIndex].nbAccount; i++)
    {
      if (!strncmp
	  (accountId, custs->c[customerIndex].accounts[i].accountId,
	   strlen (accountId) - 1))
	{
	  break;
	}
    }

  if (i == custs->c[customerIndex].nbAccount)
    {
      fprintf (stderr, "\nAucun compte ne correspond\n");
      i = -1;
    }
  return i;
}

// retourne un indice de client, 0 si l'authentification n'a pas réussi
int
authenticate (customerArray * custs, char *id, char *pw)
{
  int i;

  for (i = 0; i < custs->nbCustomers; i++)
    {
      if (!strcmp (custs->c[i].id, id))
	break;
    }

  if (i == custs->nbCustomers)
    {
      fprintf (stderr, "\nImpossible de trouver le client");
      i = -1;
    }
  else
    {
      // Les password sont identifiés par un linefeed

      if (strncmp (pw, custs->c[i].pw, strlen (pw)))
	{
	  fprintf (stderr, "\nMauvais mot de passe");
	  i = -1;
	}
    }

  return i;
}

// Affiche la structure de clients
void
display (customerArray * custs)
{
  int j = 0, i = 0;

  printf ("\n");
  for (i = 0; i < custs->nbCustomers; i++)
    {
      printf (custs->c[i].id);
      for (j = 0; j < custs->c[i].nbAccount; j++)
	{
	  printf ("\n\t");
	  printf (custs->c[i].accounts[j].accountId);
	  printf ("\t = %.2f", custs->c[i].accounts[j].balance/100.00);
	}
      printf ("\n");
    }
  fflush (stdout);
}

// Libère la structure de clients
int
liberateCustomerArray (customer * custs, int nbCustomers)
{
  int i, j, k;
  for (i = 0; i < nbCustomers; i++)
    {
      free (custs[i].id);
      free (custs[i].pw);
      for (j = 0; j < custs[i].nbAccount; j++)
	{
	  free (custs[i].accounts[j].accountId);

	  for (k = 0; k < custs[i].accounts[j].nbOps - 1; k++)
	    {
	      free (custs[i].accounts[j].ops[k].date);
	      //free(&custs[i].accounts[j].ops[k]);
	    }
	  free (custs[i].accounts[j].ops);
	}
      free (custs[i].accounts);
    }
  free (custs);
  return EXIT_SUCCESS;
}

// Récupère les comptes d'un FILE * ouvert en mode lecture
void
getAccountsFrom (FILE * fa, customerArray * custs)
{
  int nChar, i = 0;
  size_t bufS = BUFFER_SIZE;
  size_t szToAlloc = 0;
  char *accountId = NULL, *tmp = NULL, *bal = NULL;
  account *copy = NULL;
  nChar = getline (&accountId, &bufS, fa);

  while (nChar >= 0)
    {
      strtok_r (accountId, SEPARATOR_STR, &tmp);

      for (i = 0; i < custs->nbCustomers; i++)
	{
	  // On a trouvé le proprietaire du compte
	  if (!strcmp (custs->c[i].id, accountId))
	    {

	      strtok_r (tmp, SEPARATOR_STR, &bal);
	      szToAlloc =
		sizeof (custs->c[i].accounts) + sizeof (account) +
		sizeof (int) + sizeof (operation);
	      // On réaloue la taille pour avoir un bloc mémoire
	      // contigü afin d'utiliser comme un tableau
	      copy = NULL;
	      while (!copy)
		copy = realloc (custs->c[i].accounts, szToAlloc);

	      custs->c[i].accounts = copy;
	      custs->c[i].accounts[custs->c[i].nbAccount].balance = 0;
	      custs->c[i].accounts[custs->c[i].nbAccount].accountId = NULL;
	      custs->c[i].accounts[custs->c[i].nbAccount].accountId =
		malloc (strlen (tmp) + 1);

	      // On copie
	      memmove (custs->c[i].accounts[custs->c[i].nbAccount].accountId,
		       tmp, strlen (tmp) + 1);
	      custs->c[i].accounts[custs->c[i].nbAccount].balance =
		atoll (bal);
	      // On initialise le pointeur d'opérations
	      custs->c[i].accounts[custs->c[i].nbAccount].ops = NULL;
	      custs->c[i].accounts[custs->c[i].nbAccount].nbOps = 0;

	      custs->c[i].nbAccount++;
	    }
	}
      nChar = getline (&accountId, &bufS, fa);
    }

  free (accountId);
}



// Crée le tableau de clients à partir d'un FILE * ouvert en lecture
size_t
createCustDatabase (customerArray * custs, FILE * fc, char *id, char *pw)
{

  size_t szToAlloc = 0;
  size_t bufS = BUFFER_SIZE;
  int nCharC, i = 0;
  customer *copy = NULL;

  custs->c = NULL;
  custs->nbCustomers = 0;

  nCharC = getline (&id, &bufS, fc);
  szToAlloc = (size_t) sizeof (custs->c);
  while (nCharC >= 0)
    {

      strtok_r (id, SEPARATOR_STR, &pw);
      szToAlloc +=
	sizeof (customer) + strlen (id) + 2 + strlen (pw) + sizeof (int);
      copy = NULL;
      while (!copy)
	{
	  copy = realloc (custs->c, szToAlloc);
	}
      custs->c = copy;
      custs->c[i].id = malloc (strlen (id) + 1);
      custs->c[i].pw = malloc (strlen (pw) + 1);
      memmove (custs->c[i].id, id, (size_t) strlen (id) + 1);
      memmove (custs->c[i].pw, pw, (size_t) strlen (pw));
      custs->c[i].nbAccount = 0;
      custs->c[i].accounts = NULL;
      nCharC = getline (&id, &bufS, fc);
      i++;
    }
  custs->nbCustomers = i;

  free (id);
  return szToAlloc;
}

int
getClientsAndAccountFrom (const char *clientFilename,
			  const char *accountFileName, customerArray * custs)
{

  char *id = NULL, *pw = NULL;
  FILE *fc = fopen (clientFilename, "r"), *fa = fopen (accountFileName, "r");

  if (!fc)
    {
      fprintf (stderr, "Fichier de clients manquants");
      return EXIT_FAILURE;
    }
  if (!fa)
    {
      fprintf (stderr, "Fichier de comptes manquants");
      return EXIT_FAILURE;
    }

  createCustDatabase (custs, fc, id, pw);

  getAccountsFrom (fa, custs);

  free (id);
  free (pw);
  fclose (fc);
  fclose (fa);

  return EXIT_SUCCESS;
}
