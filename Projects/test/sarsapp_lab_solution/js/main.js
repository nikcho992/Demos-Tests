$(document).ready(function(){
	$('.socialContainer').hover(function(){
		$(this).stop().animate({
			'opacity': 1,
			'marginTop': '20px'
		}, 500);
	}, function(){
		$(this).stop().animate({
			'opacity': '0.5',
			'marginTop': '40px'
		}, 500, "easeOutBounce");
	});

	$('.socialContainer').tooltipster();
	$('#logOut').tooltipster();
});