	// Bibliotéques
var express = require('express');
var cookieParser = require('cookie-parser')
var fs = require('fs');
var connect = require('connect');
var mysql = require('mysql');
var app = express();
app.use(cookieParser());

var server = app.listen(8080);

// Fichier CSS
app.get('/css/:file.css', function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/css'});
	var path = 'public/css/'+req.params.file+'.css';
	res.write(fs.readFileSync(path, 'utf8'));
	res.end();
});

// Fichier JS
app.get('/:file.js', function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/javascript'});
	res.write(fs.readFileSync('public/js/'+req.params.file+'.js', 'utf8'));
	res.end();
});

// Fichier font
app.get('/fonts/:file', function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/javascript'});
	res.write(fs.readFileSync('public/fonts/'+req.params.file, 'utf8'));
	res.end();
});

// Le client demange le template (défaut à l'ouverture de la page)
app.get('/', function (req, res) {
	res.render('template.ejs');
});



var io = require('socket.io').listen(server);

io.sockets.on('connection', function (socket) {

	console.log("Un client essai de se connecter");

	socket.emit('connexion_ok', 1);

	socket.on('disconnect', function () {
     	console.log('déconnecté');
    });

	


});

// Quand on quitte le programme
process.on('SIGINT', function () {
	console.log("Sauvegarde en cours...");
	console.log("Données sauvegardée.");
    process.exit(0);
});


