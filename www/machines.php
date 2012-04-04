<?php
$machines = NULL;

function chargerMachines(){
	$fp = fopen("machines.txt","r");
	if (!$fp) {
		echo "Impossible d'ouvrir le fichier";
		exit;
	}

	else {
		$i = 0;
		while(!feof($fp)) {
			$ligne = fgets($fp, 255);
			$ligne = explode(" ", $ligne);
			if(count($ligne) == 3){
				$machines[$i][0]=$ligne[0];
				$machines[$i][1]=$ligne[1];
				$machines[$i][2]=$ligne[2];
				$i++;
			}else{
				echo "Erreur dans les données de machines.txt";
			}
		}
		fclose($fp);
	}
	return $machines;
}

function sauverMachines($machines){
	$fp = fopen("machines.txt","w+");
	if (!$fp) {
		echo "Impossible d'ouvrir le fichier";
		exit;
	}

	else {
		for($i = 0; $i < count($machines); $i++){
			fputs($fp, $machines[$i][0]." ".$machines[$i][1]." ".$machines[$i][2]);
		}
		fclose($fp);
	}
}

function ajouterMachine($machines, $host, $user, $pwd, $path, $exe){
	$nbMachines = count($machines);
	$machines[$nbMachines][0]=$host;
	$machines[$nbMachines][1]=$user;
	$machines[$nbMachines][2]=$pwd;
	if($path)
		$machines[$nbMachines][3]=$path;
	if($exe)
		$machines[$nbMachines][4]=$exe;
	return $machines;
}

function enleverMachine($machines, $host){
	for($i = 0; $i < count($machines); $i++)
		if($machines[$i][0] == $host){
			unset($machines[$i]);
			return $machines;
		}

	return $machines;
}