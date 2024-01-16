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

server {
    host = 127.0.0.1
    port = 8080
    server_names = localhost, example1.com
    default_server = true
    error_pages = 404.html, 500.html
    client_body_limit = 10M

    [server.routes]
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

server {
    host = 127.0.0.1
    port = 9090
    server_names = example2.com
    default_server = false
    error_pages = 404_custom.html
    client_body_limit = 5M

    [server.routes]
    route1 {
        path = /
        accepted_methods = GET
        directory = /var/www/second_server
        index_file = home.html
        enable_directory_listing = true
    }
}


////

RICHIESTE HTML

Esempio di richiesta GET:

GET /resource HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0


Esempio di richiesta POST con JSON:

POST /resource HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0
Content-Type: application/json
Content-Length: 18

{"key":"value"}


Esempio di richiesta DELETE:

DELETE /resource/123 HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0


Esempio di richiesta di upload di un file:

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


oppure

POST /upload HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryABC123
Content-Length: ...

------WebKitFormBoundaryABC123
Content-Disposition: form-data; name="file"; filename="yellow_pixel.png"
Content-Type: image/png

‰PNG
\x0D\x0A
\x1A\x0A
\x00\x00\x00\x0DIHDR\x00\x00\x00\x01\x00\x00\x00\x01\x08\x06\x00\x00\x00\x1F\x15\xC4\x89\x00\x00\x00\x0AIDAT\x08\xD7c\xF8\xFF\xFF\x3F\x00\x05\xFE\x02\x00\x00\x00\x00IEND\xAE\x42\x60\x82
------WebKitFormBoundaryABC123--
