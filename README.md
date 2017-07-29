# text_mining


### Pour lancer le projet :
`./configure` pour un premier lancement 

`make` génère le binaire dans le dossier out

`./text_mining -h` permet de voir comment lancer le programme.

`make doc` génère la documentaion dans le dossier out
#### NB:
même si le makefile à la racine semble ne servir à rien, laissez le, ça evite d'aller le chercher dans le dossier build.



### Questions:
==========
 1.	Decrivez les choix de design de votre programme
Le trie est representé par un vecteur de noeuds (la classe trie::Node). Ce vecteur, contenu dans le fichier nodes.cc est dans un namespace anonyme. Il est initialiser au premier appel du getter (trie::get_node()) ou du setter (trie::add_node()). De cette façon, on peut le considerer commme un singleton, ce qui nous permet d'être sûr de ne pas avoir de duplicat.
Les noeuds du trie sont representés par la classe trie::Node. Cette classe ne contient qu'un vecteur de children. Ce vecteur contient les aretes vers les fils du noeud actuel. A chaque arete est associée une lettre, l'index de ce noeud fils dans le vecteur de nodes, ainsi que la frequence du mot decrit par la suite de node permettant d'arriver au children. Si le node ne represente pas une fin de mot, la fréquence est à zéro. Les données contenues dans le vecteur children ont été mis dans une structure qui a permis d'optimiser l'espace : l'utilisation d'une bitfield a permis d'eviter 7 bits de padding.

 2.	Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)

 3.	Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?

 4.	Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?
Utilisation d'un trie.
structure la plus optimiser, et relativement simple a implementer. Nous avons envisager de faire un Patricia Trie, mais cela aurait necessité un parcourt integrale du trie afin de modifier les index des fils dans le vecteur children. Nous avons cependant jugé que notre structure de données était suffisamment optimisée pour ne pas implementer de Patricia Trie.

 5.	Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats

 6.	Comment comptez vous améliorer les performances de votre programme

 7.	Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?
Il manquera par exemple le correction relative au clavier. Ainsi, si le mot est incorrect, mais qu'il y a un z, on pourra envisager de le remplacer par un "a", un "e" ou un "s"
