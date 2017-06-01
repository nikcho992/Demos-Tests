<?php
	session_start();
	
	/* if have logged user redirect to home page */
    if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']= true){
        header('Location: home.php');
	}

	require_once 'php/addbuttonsfunctions.php';
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Login Page</title>
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" type="text/css" href="css/tooltipster.css">
	<script type="text/javascript" src="js/libs/jquery-2.0.3.min.js"></script> 
	<script type="text/javascript" src="js/libs/jquery.easing.1.3.js"></script>
	<script type="text/javascript" src="js/libs/jquery.tooltipster.min.js"></script>
	<script type="text/javascript" src="js/main.js"></script>
	<script type="text/javascript" src="js/oauthpopup.js"></script>
	<script type="text/javascript" src="js/authpopupfunctions.js"></script>
	<script type="text/javascript">
		$(document).ready(function(){
			callFbAuthPopup();
			callGPlusAuthPopup();
			callTwitterAuthPopup();
		});
	</script>
</head>
<body>
	<section>
		 <div id="mainSocialContainer">
			<header>
				<div id="socialTitle">
					<h1>Влез чрез соц. мрежа</h1>
				</div>
			</header>
			<div class="clear" id="buttonsDiv">	
				<?php
					addFbButton();
					addTwitterButton();
					addGPlusButton();
				?>			
			</div>
		</div> 
	</section>
</body>
</html>