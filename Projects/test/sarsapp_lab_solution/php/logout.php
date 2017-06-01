<?php

	session_start();
	session_destroy();
	
	//redirect to index.php
	header('Location: /sarsapp/index.php');
	
?>