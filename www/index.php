<?php
require_once "config.php";
require_once "machines.php";
require_once "affiche.php";
include "header.html";
$machines = NULL;
chargerMachines();


if(isset($_GET['action'])){
	if(!isset($_GET['confirm']))
		afficherFormulaire();
	else{
		$host = $_POST['host'];
		$user = $_POST['user'];
		$path = NULL;
		$exe=NULL;
		if(isset($_POST['path'])){
		 	$path = $_POST['path'];
			if(isset($_POST['exe'])) 
				$exe = $_POST['exe'];
		}
		ajouterMachine($host, $user, $path, $exe);
		sauverMachines();
	}
}
if(isset($_GET['remove'])){
	enleverMachine($_GET['remove']);
	sauverMachines();
}



afficherMachines();
echo '<p><a href="?view=all">Voir toutes les config</a> - <a href="?action=add">Ajouter une machine</a></p>';



if(isset($_GET['view'])){
	if($_GET['view'] == 'all')
		afficherToutesLesConfig();
	else
		afficherUneConfig($_GET['view']);
}


sauverMachines();
include "footer.html";