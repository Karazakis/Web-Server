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

lavori da fare
parsing config file
parsing richiesta http
utils


/////

CONFIG FILE DA PARSARE

[servers]
server1 {
    host = 127.0.0.1
    port = 8080
    server_names = localhost, example1.com
    default_server = true
    error_pages = 404.html, 500.html
    client_body_limit = 10M

    [server1.routes]
    route1 {
        path = /
        accepted_methods = GET, POST
        directory = /var/www/default
        index_file = index.html
        enable_directory_listing = true
    }

    route2 {
        path = /kapouet
        accepted_methods = GET
        directory = /tmp/www
        index_file = index.html
        enable_directory_listing = false
    }

    route3 {
        path = /redirect
        http_redirect = http://www.example1.com/new-location
    }

    route4 {
        path = /cgi-bin/script.php
        accepted_methods = GET, POST
        cgi_executable = /usr/bin/php-cgi
    }

    route5 {
        path = /upload
        accepted_methods = POST
        upload_enabled = true
        upload_directory = /var/www/uploads
    }
}

server2 {
    host = 127.0.0.1
    port = 9090
    server_names = example2.com
    default_server = false
    error_pages = 404_custom.html
    client_body_limit = 5M

    [server2.routes]
    route1 {
        path = /
        accepted_methods = GET
        directory = /var/www/second_server
        index_file = home.html
        enable_directory_listing = true
    }

    # Aggiungi altre configurazioni delle route per il secondo server se necessario
}


////

RICHIESTE HTML

Esempio di richiesta GET:

http

GET /resource HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0

Esempio di richiesta POST con JSON:

http

POST /resource HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0
Content-Type: application/json
Content-Length: 18

{"key":"value"}

Esempio di richiesta PUT con JSON:

http

PUT /resource/123 HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0
Content-Type: application/json
Content-Length: 18

{"key":"value"}

Esempio di richiesta DELETE:

http

DELETE /resource/123 HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0

Esempio di richiesta di upload di un file:

http

POST /upload HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryABC123
Content-Length: ...

------WebKitFormBoundaryABC123
Content-Disposition: form-data; name="file"; filename="example.txt"
Content-Type: text/plain

Contenuto del file qui...

------WebKitFormBoundaryABC123-