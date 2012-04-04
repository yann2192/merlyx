<?php
require_once "config.php";
require_once "machines.php";

function afficherConfig($connexionType, $user, $host, $path, $exeName){
	echo exec($connexionType." ".$user." ".$host ." \"".$path."/".$exeName."\"", $return);
	var_dump($return);
}



$machines = chargerMachines();
afficherMachines($machines);
sauverMachines($machines);
//afficherConfig($connexionType, $user, $host, $merlyxPath, $exeName);