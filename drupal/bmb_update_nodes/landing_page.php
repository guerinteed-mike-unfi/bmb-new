<!DOCTYPE html>
<?php
$var = 0;
if(isset($_GET['del']) && $_GET['del'] != "") { 
  $var = $_GET['del']; 
}
if($var == 1) { 
?>
<html>
    <head>
        <title>Blue Marble Brands Product Update Sites</title>
        <meta name="description" content="Blue Marble Brands Product Update Script">
            <link rel="stylesheet" type="text/css" media="all" href="./css/styles.css">
    </head>
    
    <body>
        <div class="header">
            <h1>Blue Marble Brands Product Update Script</h1>
        </div>
        <div class="UpdateScript" style="border: double;">
            <h2>All Files has been Deleted!</h1>
        </div>
        <div class="footer"></div>
    </body>
</html>


<?php } else { ?>
<html>
    <head>
        <title>Blue Marble Brands Product Update Sites</title>
        <meta name="description" content="Blue Marble Brands Product Update Script">
            <link rel="stylesheet" type="text/css" media="all" href="./css/styles.css">
    </head>
    
    <body>
        <div class="header">
            <h1>Blue Marble Brands Product Update Script</h1>
        </div>
        <div class="UpdateScript" style="border: double;">
            <h2>Scripts run has been completed!</h1>
            
            <form action="/delete_sites.php" name="delete_files" method="post"></label><br/>
                <input type="submit" value="Delete Files From Recent Run" class="FormSubmit" onclick="return confirm('All files will be deleted, Are you sure?')" />
            </form>
        </div>
        <div class="footer"></div>
    </body>

</html>

<?php } ?>