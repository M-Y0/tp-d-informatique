# tp-d-informatique

#### 1. Message de Bienvenue et Prompt Simple
- À son démarrage, le shell affiche un message de bienvenue et un prompt (`enseash %`) qui invite l'utilisateur à entrer des commandes.
- **Fonctions Clés Utilisées** : `write` pour afficher le message et le prompt.

#### 2. Exécution de Commandes
- Le shell lit et exécute les commandes saisies par l'utilisateur.
- **Fonctions Clés Utilisées** : 
  - `read` pour lire la commande de l'utilisateur.
  - `strtok` pour découper la commande en tokens (mots).
  - `executeCommand`, une fonction personnalisée qui utilise `fork` pour créer un processus enfant et `execvp` pour exécuter la commande.

#### 3. Sortie du Shell
- L'utilisateur peut quitter le shell en tapant `exit` ou en utilisant <ctrl>+d.
- **Fonctions Clés Utilisées** : `strcmp` pour comparer la commande saisie avec la chaîne "exit".

#### 4. Affichage du Code de Retour
- Après chaque commande, le shell affiche le code de retour ou le signal reçu par la commande précédente.
- **Fonctions Clés Utilisées** :
  - `WIFEXITED` et `WEXITSTATUS` pour vérifier si le processus enfant s'est terminé normalement et obtenir son code de sortie.
  - `WIFSIGNALED` et `WTERMSIG` pour vérifier si le processus enfant a été arrêté par un signal et obtenir le numéro de ce signal.

#### 5. Mesure du Temps d’Exécution
- Le shell mesure et affiche le temps d'exécution de chaque commande.
- **Fonctions Clés Utilisées** : `clock_gettime` pour obtenir le temps avant et après l'exécution de la commande.

#### 6. Exécution de Commandes Complexes (avec Arguments)
- Le shell est capable d'exécuter des commandes avec des arguments.
- **Fonctions Clés Utilisées** : La même logique que pour l'exécution des commandes simples, mais en prenant en compte les tokens supplémentaires pour les arguments.

#### 7. Gestion des Redirections (`<`, `>`)
- Le shell prend en charge les redirections de `stdin` et `stdout`.
- **Fonctions Clés Utilisées** :
  - `open` pour ouvrir les fichiers de redirection.
  - `dup2` pour rediriger `stdin` ou `stdout` vers les fichiers ouverts.
  - Cette logique est intégrée dans `executeCommand`.

