var socket = null;

function stopAll(msg) {
	if (!msg)
		msg = 'Force disconnect';
	socket.close();
	socket = null;
	$('body').html(msg);
}

function CanvasObject() {
	this.color = "red";
	this.canvas = $("#canvas");
	this.context = this.canvas[0].getContext('2d');
	this.width_brush = 3;
	this.draw = false;
	this.last = null;
	var that = this;

	this.drawLine = function(a, b) {
		this.context.beginPath();
		this.context.moveTo(a.x, a.y);
		this.context.lineTo(b.x, b.y);
		this.context.strokeStyle = this.color;
		this.context.lineWidth = this.width_brush;
		this.context.stroke();
	}

	this.getPositionCursor = function(e) {
		 var parentOffset = that.canvas.parent().offset(); 
   		var relX = e.pageX - parentOffset.left;
   		var relY = e.pageY - parentOffset.top;
   		return {x: relX, y: relY};
	}

	this.canvas.mousedown(function(e) {
		that.last = that.getPositionCursor(e);
		that.draw = true;
	});

	this.canvas.mouseup(function() {
		that.draw = false;
	});

	this.canvas.mousemove(function(e) {
		if (that.draw) {
			var pos = that.getPositionCursor(e);
			socket.emit('drawLine', that.last, pos);
			that.drawLine(that.last, pos);
			that.last = pos;
		}
	});
}

var canvasObj;

function start_loading(login) {
	
	socket = io.connect('http://localhost:8080');

	socket.on('drawLine', function(a, b) {
		console.log(a);
		canvasObj.drawLine(a,b);
	});


	socket.on('close', function() {
		stopAll();
	});
	socket.on('disconnect', function() {
		stopAll();
	});

}

$(document).ready(function() {

start_loading('doelia');
canvasObj = new CanvasObject();
	

});




