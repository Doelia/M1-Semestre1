var socket = null;

function stopAll(msg) {
	if (!msg)
		msg = 'Force disconnect';
	socket.close();
	socket = null;
	$('body').html(msg);
}

function start_loading(login) {
	
		socket = io.connect('http://pc.doelia.fr:8080');
		socket.on('connexion_ok', function() {

		});
		socket.on('close', function() {
			stopAll();
		});
		socket.on('disconnect', function() {
			stopAll();
		});
	}, delay_fake);
}

$(document).ready(function() {
	start_loading();
	processElements();
});




