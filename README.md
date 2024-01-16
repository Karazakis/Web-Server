# Web-Server

// PER USARE GIT HUB

prima bisogna aver messo su setting del proprio profilo la ssh key nel file id rsa pub.pub dell vostro pc nella cartella home/.ssh
git remote set-url origin git@github.com:Karazakis/Web-Server.git // per fare il push senza auth


// PER PUSHARE 

-prima pullare per integrare le modifiche fatte da altri 

git pull origin nome-del-tuo-branch (o master o main)  o git pull e basta dopo aver fatto il clone

-poi checkare se ci sono conflitti(cioe' modifiche alla stessa parte di codice)
git status

-se ci sono conflitti (da evitare in fase di gestione task) correggere a mano i file

poi il classico:

- git add
- git commit
- git push


////////////////////

