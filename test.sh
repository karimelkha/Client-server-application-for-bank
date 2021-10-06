#!/bin/sh 
make;

#./server &
#Récupération du pid du serveur
#pid=$!;

sleep 0.5;

echo testLog;

testDirectory="./test/";
testLog="testLog"
# Teste tout les fichiers tst du répertoire de test en TCP et UDP 
for TEST in ${testDirectory}*.tst;do
     # on lance valgrind en indiquant un code
     # de retour à 3 si une erreur survient 
     valgrind --leak-check=full --error-exitcode=3 ./client 127.0.0.1 < $TEST;  
     #On teste si une erreur mémoire est survenue
     if [ $? = 3 ];then
         echo " TCP : Erreur mémoire lors du test\n"$TESTS >> $testDirectory$testLog ;
     else
          echo $TEST" TCP : passed\n" >>     $testDirectory$testLog ;
     fi
        #TESTS UDP
       valgrind --leak-check=full --error-exitcode=3 ./client UDP 127.0.0.1 < $TEST;  
       if [ $? = 3 ];then
           echo " UDP : Erreur mémoire lors du test "$TESTS"\n" >>  $testDirectory$testLog ;
      else
          echo $TEST" UDP : passed\n" >>  $testDirectory$testLog ;
       fi
done

sleep 0.5;
#pkill server
