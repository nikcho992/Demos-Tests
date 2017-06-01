<?php
//file which have information for connecting to facebook
require 'fbconfig.php';
//facebook library for php 
require 'lib/facebook/facebook.php';

$facebook = new Facebook(array(
        'appId'     =>  $fb_appID,
        'secret'    => 	$fb_appSecret,
        ));
		
//getting facebook user id of the current user
$user = $facebook->getUser();

//if user id is not empty save some information for user
if($user){
	try{
	
		//'/me' for the logged in user's profile.
		$user_profile = $facebook->api('/me');
		$_SESSION['user_info'] = $user_profile;
		//set variable which indicate if have user login 
		$_SESSION['loggedin'] = true;
		//set which social network is used
		$_SESSION['socialnetwork'] = 'facebook';
			
		}catch(FacebookApiException $e){
		
			error_log($e);
			$user = NULL;
			
		}
}	
//if user id is empty
if(empty($user)){

	//get login url for user
	$loginurl = $facebook->getLoginUrl(array(
					// parameter 'scope' - list of permissions to request from the user. May to be used if more information for user is wanted. 
					// For this application only basic information is used and this parameter is no needed. But you may try to get more informaion. 
					//'scope'=> 'email,read_stream, publish_stream, user_birthday, user_location, user_work_history, user_hometown, user_photos',
					//The URL to redirect the user to once the login/authorization process is complete.
					'redirect_uri' => 'http://localhost:8080/sarsapp/php/fblogin.php',
					//The display mode in which to render the dialog.
					'display'=>'popup'
					));
	// send user to facebook login page
	header('Location: '.$loginurl);
	
}	
?>
<!-- after getting all needed information for user close popup-->
<script type="text/javascript">
window.close();
</script>