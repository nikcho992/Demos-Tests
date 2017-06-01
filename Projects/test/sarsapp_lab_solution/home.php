<?php
session_start();
/* check if have user which is already log in. If don't have logged user redirect to index page */
if(!isset($_SESSION['loggedin']) || $_SESSION['loggedin'] = false){
    header('Location: index.php');
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>User profil</title>
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" type="text/css" href="css/tooltipster.css">
	<script type="text/javascript" src="js/libs/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/libs/jquery.easing.1.3.js"></script>
	<script type="text/javascript" src="js/libs/jquery.tooltipster.min.js"></script>
	<script type="text/javascript" src="js/main.js"></script>
</head>
<body>
	<div id="wrapper">
		<header>
			<div id="header">
				<div id="userProfileContainer" class="clear">
					<a href="php/logout.php" id="logOut" title="Изход"><span></span></a>
					<?php 
						echo '<span id="user">'. $_SESSION['user_info']['name'] .'</span>';
					?>	
				</div>
			</div>
		</header>
		<section>
			<div id="mainContentContainer">
			<?php 
				echo 'You successufully logged by your ';
				if($_SESSION['socialnetwork'] == 'facebook'){ 
					echo 'FACEBOOK account';
				} else if($_SESSION['socialnetwork'] == 'twitter'){ 
					echo 'TWITTER account';
				}else if($_SESSION['socialnetwork'] == 'gplus'){ 
					echo 'GOOGLE+ account';
				} 
			?>
			</div>	
		</section>
	</div>
</body>
</html>