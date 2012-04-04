<?php
function afficherConfig($user, $host, $path, $exeName){
	global $rasPath;
	$option = "-I ".$rsaPath;
	$cmd = '"'.$path.'/'.$exeName.'"';
	$cmdLine = "ssh ".$option." ".$user."@".$host." ".$cmd;
	echo exec($cmdLine, $return);
	var_dump($return);
}

function afficherToutesLesConfig(){
	global $machines;
	global $merlyxPath;
	global $exeName;
	for($i = 0; $i < count($machines); $i++){
		$host = $machines[$i][0];
		$user = $machines[$i][1];
		$mdp = $machines[$i][2];
		if(isset($machines[$i][3]))
			$path = $machines[$i][3];
		else
			$path = $merlyxPath;
		if(isset($machines[$i][4]))
			$exe = $machines[$i][4];
		else
			$exe = $exeName;
		afficherConfig($user, $host, $path, $exe);
	}
}

function afficherUneConfig($host){
	global $machines;
	$i = 0;
	for(; $machines[$i][0] <> $host && $i <= count($machines); $i++);
	if($i == count($machines)) echo 'Machine introuvable.';
	else{
		global $merlyxPath;
		global $exeName;
		$host = $machines[$i][0];
		$user = $machines[$i][1];
		$mdp = $machines[$i][2];
		if(isset($machines[$i][3]))
			$path = $machines[$i][3];
		else
			$path = $merlyxPath;
		if(isset($machines[$i][4]))
			$exe = $machines[$i][4];
		else
			$exe = $exeName;
		afficherConfig($user, $host, $path, $exe);
	}
}