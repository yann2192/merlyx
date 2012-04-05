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
		if(isset($machines[$i][2]))
			$path = $machines[$i][2];
		else
			$path = $merlyxPath;
		if(isset($machines[$i][3]))
			$exe = $machines[$i][3];
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
		if(isset($machines[$i][2]))
			$path = $machines[$i][2];
		else
			$path = $merlyxPath;
		if(isset($machines[$i][3]))
			$exe = $machines[$i][3];
		else
			$exe = $exeName;
		afficherConfig($user, $host, $path, $exe);
	}
}

function afficherFormulaire(){
	?><form method="post" action="?action=add&confirm=true">
	<p>
		<label for="host">host :</label>
		<input type="text" name="host" id="host" required/>
	</p>
	
	<p>
		<label for="user">user :</label>
		<input type="text" name="user" id="user" required/>
	</p>
	
	<p>
		<label for="path">merlyx path :</label>
		<input type="text" name="path" id="path" />
	</p>
	
	<p>
		<label for="exe">executable name :</label><br />
		<input type="text" name="exe" id="exe" />
	</p>
	
	<p>
		<input type="submit" value="Envoyer" />
	</p>
</form><?php
}