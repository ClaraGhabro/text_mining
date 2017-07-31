# text_mining


### Pour lancer le projet :
`./configure` pour un premier lancement 

`make` génère les binaires à la racine

`make doc` génère la documentaion dans le dossier out

#### NB:
même si le makefile à la racine semble ne servir à rien, laissez le, ça evite d'aller le chercher dans le dossier build.



### Questions:
==========
 1.	Decrivez les choix de design de votre programme
Le trie est representé par un vecteur de noeuds (la classe trie::Node). Ce vecteur, contenu dans le fichier nodes.cc est dans un namespace anonyme. Il est initialiser au premier appel du getter (trie::get_node()) ou du setter (trie::add_node()). De cette façon, on peut le considerer commme un singleton, ce qui nous permet d'être sûr de ne pas avoir de duplicat.
Les noeuds du trie sont representés par la classe trie::Node. Cette classe ne contient qu'un vecteur de children. Ce vecteur contient les aretes vers les fils du noeud actuel. A chaque arete est associée une lettre, l'index de ce noeud fils dans le vecteur de nodes, ainsi que la frequence du mot decrit par la suite de node permettant d'arriver au children. Si le node ne represente pas une fin de mot, la fréquence est à zéro. Les données contenues dans le vecteur children ont été mis dans une structure qui a permis d'optimiser l'espace : l'utilisation d'une bitfield a permis d'eviter 7 bits de padding.

 2.	Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)
tous les tests effectués sont regroupés dans le fichiers test.txt, qui a également été testé firectement.
Pour chaque test effectué sur notre binaire et effectué sur le binaire de référance. On compare ensuite les output avec un diff

 3.	Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?
Aucun rapport, mais il a été surprenant (et pourtant un peu évident) que deux lettres identiques a la suite soient considérée comme un echange de lettre, augmantant ainsi la distance de 1 ...

 4.	Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?
Utilisation d'un trie.
structure la plus optimiser, et relativement simple a implementer. Nous avons envisager de faire un Patricia Trie, mais cela aurait necessité un parcourt integrale du trie afin de modifier les index des fils dans le vecteur children. Nous avons cependant jugé que notre structure de données était suffisamment optimisée pour ne pas implementer de Patricia Trie.

 5.	Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats
On pourrait par exemple parcourir le trie, en effectuant les calculs de distance, et "mettre sur pause" un parcours d'arbres qui donnerait une distance plus grande que le minimum actuel trouvé. On conserverit ensuite les mots dont la distance est minimale.

 6.	Comment comptez vous améliorer les performances de votre programme
possibilité de rajouter des tests pour que la recherche soit plus rapide : ne pas explorer certaines branche du trie en se basant sur des conditions relatives a la taille actuelle du mot, et a la distance maximale avec le mot initial.
Optimisation de la structure de données du trie. Chaque noeud fait 24 octets, il doit y avoir moyen de descendre en dessous (vu les perfs de la ref)

 7.	Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?
Il manquera par exemple le correction relative au clavier. Ainsi, si le mot est incorrect, mais qu'il y a un z, on pourra envisager de le remplacer par un "a", un "e" ou un "s"
Correction d'accent (formee non normalisée)
certains correcteurs prennent en compte les abreviations, et les "expend"
