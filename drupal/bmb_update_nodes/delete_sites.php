<?php
$file = getcwd().DIRECTORY_SEPARATOR.'delete_bmb_files.bat';
if(system("cmd /c ".$file)){
    header("Location: landing_page.php?del=1");
}
//print "<br/>All files deleted";

?>