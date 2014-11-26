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

}

$(document).ready(function() {

	var color = "green";
	var canvas = $("#canvas");
	var context = canvas[0].getContext('2d');
	var painting = false;
	var started = false;
	var width_brush = 1;

	function drawLine() {
		if (!started) {
			context.beginPath();
			context.moveTo(cursorX, cursorY);
			started = true;
		} 
		else {
			context.lineTo(cursorX, cursorY);
			context.strokeStyle = color;
			context.lineWidth = width_brush;
			context.stroke();
		}
	}

	canvas.mousedown(function(e) {
		painting = true;
		cursorX = (e.pageX - this.offsetLeft);
		cursorY = (e.pageY - this.offsetTop);
	});

	$(this).mouseup(function() {
		painting = false;
		started = false;
	});

	canvas.mousemove(function(e) {
		if (painting) {
			cursorX = (e.pageX - this.offsetLeft) - 10; 
			cursorY = (e.pageY - this.offsetTop) - 10;
			drawLine();
		}
	});

});




