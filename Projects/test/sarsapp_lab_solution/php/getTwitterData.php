<?php
	ob_start();
	
	require("lib/twitter/twitteroauth.php");
	require 'twitterconfig.php';
	session_start();

	if (!empty($_GET['oauth_verifier']) && !empty($_SESSION['oauth_token']) && !empty($_SESSION['oauth_token_secret'])) {
		// We've got everything we need
		$twitteroauth = new TwitterOAuth($CONSUMER_KEY, $CONSUMER_SECRET, $_SESSION['oauth_token'], $_SESSION['oauth_token_secret']);
		// Let's request the access token
		$access_token = $twitteroauth->getAccessToken($_GET['oauth_verifier']);
		// Let's get the user's info
		$user_info = $twitteroauth->get('account/verify_credentials');
		if (isset($user_info->error)) {
			// Something's wrong, go back to square 1  
			header('Location: twitterlogin.php');
		} else {
			// Get user info and save it in 
		   $username = $user_info->name;
		   $user_info = array( "name" => $username );
		   $_SESSION['user_info'] = $user_info;
		   $_SESSION['socialnetwork'] = 'twitter';
		   $_SESSION['loggedin'] = true;
		   ?>
		   <script type="text/javascript">
				window.close();
			</script>
		   <?php
		}
	} else { 
		// Something's missing, go back to square 1
		header('Location: twitterlogin.php');
	}
?>
