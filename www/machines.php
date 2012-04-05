<?php


function chargerMachines(){
	global $machines;
	$fp = fopen("machines.txt","r");
	if (!$fp) {
		echo "Impossible d'ouvrir le fichier";
	}

	else {
		$i = 0;
		while(!feof($fp)) {
			$ligne = fgets($fp, 255);
			$ligne = explode(" ", trim($ligne));
			if(count($ligne) >= 2){
				$machines[$i][0]=$ligne[0];
				$machines[$i][1]=$ligne[1];
				if(isset($ligne[2]))
					$machines[$i][2]=$ligne[2];
				if(isset($ligne[3]))
					$machines[$i][3]=$ligne[3];
				$i++;
			}
		}
		fclose($fp);
	}
}

function sauverMachines(){
	global $machines;
	unlink("machines.txt");
	$fp = fopen("machines.txt","w+");
	if (!$fp) {
		echo "Impossible d'ouvrir le fichier";
		exit;
	}

	else {
		for($i = 0; $i < count($machines); $i++){
			$machine = implode(" ", $machines[$i]);
			fwrite($fp, $machine."\n");
		}
		fclose($fp);
	}
}

function machineExists($host){
	global $machines;
	for($i = 0; $i < count($machines); $i++){
		if($machines[$i][0] == $host) return true;
	}
	return false;
}

function ajouterMachine($host, $user, $path, $exe){
	if(machineExists($host)) return;
	global $machines;
	$nbMachines = count($machines);

	$machines[$nbMachines][0]=$host;
	$machines[$nbMachines][1]=$user;
	if($path != NULL)
		$machines[$nbMachines][2]=$path;
	if($exe != NULL)
		$machines[$nbMachines][3]=$exe;
}

function enleverMachine($host){
	global $machines;
	for($i = 0; $i < count($machines); $i++)
		if($machines[$i][0] == $host){
			array_splice($machines, $i, 1);
			break;
		}
		var_dump($machines);
}

function afficherMachines(){
	global $machines;
	echo '<div id="machines">';
	for($i = 0; $i < count($machines); $i++){
		echo $machines[$i][0].' - '.$machines[$i][1].' &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <a href="?view='.$machines[$i][0].'">Voir la config</a> - <a href="?remove='.$machines[$i][0].'">Supprimer la machine</a><br />'; 
	}
	echo '</div>';
}