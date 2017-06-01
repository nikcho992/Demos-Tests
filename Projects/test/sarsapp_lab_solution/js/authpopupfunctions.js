
function callFbAuthPopup(){
	$('#facebook').click(function(e){
					$.oauthpopup({
						path: 'php/fblogin.php',
						width:600,
						height:300,
						callback: function(){
							window.location.reload();
						}
					});
				e.preventDefault();
				});
}

function callTwitterAuthPopup(){
	$('#twitter').click(function(e){
				$.oauthpopup({
					path: 'php/twitterlogin.php',
					width:600,
					height:300,
					callback: function(){
						window.location.reload();
					}	
				});
			e.preventDefault();
			});
}

function callGPlusAuthPopup(){
	$('#gplus').click(function(e){
				$.oauthpopup({
					path: 'php/gpluslogin.php',
					width:600,
					height:300,
					callback: function(){
						window.location.reload();
					}	
				});
			e.preventDefault();
			});
}