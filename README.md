# text_mining


### Pour lancer le projet :
`./configure` pour un premier lancement 

`make` génère le binaire dans le dossier out

`./text_mining -h` permet de voir comment lancer le programme.

`make doc` génère la documentaion dans le dossier out
#### NB:
même si le makefile à la racine semble ne servir à rien, laissez le, ça evite d'aller le chercher dans le dossier build.


stratégie : créer un nouveau trie pour chaque nouvelle premiere lettre de mot.
ex : tous les mots commencant par un 'n' seront dans un meme trie, puis tous les mots commencant par 'o' seront dans un nouveau trie, etc.
