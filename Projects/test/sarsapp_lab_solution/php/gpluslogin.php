<?php
	session_start();
	
	// include the required files for google login
	require_once 'lib/google/Google_Client.php'; 
	require_once 'lib/google/contrib/Google_PlusService.php';
	require_once 'lib/google/contrib/Google_Oauth2Service.php';
	// include file which contains conigurations used for cnnecting to google api
	require_once 'gplusconfig.php';

	//create google client
	$client = new Google_Client();

	//set client's configurations
	$client->setApplicationName($gplus_applicationName);
	$client->setScopes(array('https://www.googleapis.com/auth/userinfo.email', 'https://www.googleapis.com/auth/plus.me'));
	// Visit https://code.google.com/apis/console to generate your
	// oauth2_client_id, oauth2_client_secret, and to register your oauth2_redirect_uri.
	$client->setClientId($gplus_clientId);
	$client->setClientSecret($gplus_clientSecret);
	$client->setRedirectUri($gplus_redirectUrl);
	$client->setDeveloperKey($gplus_developerKey);
	
	$plus = new Google_PlusService($client);

	//when user authenticate your app response will contains code 
	if(isset($_GET['code'])) {
	
		// Authenticate
		$client->authenticate(); 
		$_SESSION['gplus_access_token'] = $client->getAccessToken(); 
		// get the access token here
		header('Location: http://' . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF']);
		
	}
	
	if(isset($_SESSION['gplus_access_token'])) {
		$client->setAccessToken($_SESSION['gplus_access_token']);
	}

	if ($client->getAccessToken()) {
	
	  $me = $plus->people->get('me');
	  // The access token may have been updated lazily. If you want to use this request token for more requests you must save it.
	  $_SESSION['gplus_access_token'] = $client->getAccessToken();
		if(isset($me)){ 
		
			//save information for user
			$_SESSION['loggedin'] = true;
			$_SESSION['socialnetwork'] = 'gplus';
			$user_info = array( "name" => $me['displayName'] );
			$_SESSION['user_info'] = $user_info;
			
		}
	} else {
	
		$authUrl = $client->createAuthUrl();
		header('Location:'.$authUrl);
		
	}
?>
<!-- after getting all needed information for user close popup-->
<script type="text/javascript">
	window.close();
</script>