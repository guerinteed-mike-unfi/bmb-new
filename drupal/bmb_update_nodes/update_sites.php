<!DOCTYPE html>
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
            <h2>Please select one or more sites to run the scripts:</h1>
        
            <form action="bmb_product_update.php" name="update_sites" method="post"></label><br/>
                <label class="class1"><input type="checkbox" name="filename[]" value="ahlaska" />Ahlaska</label><br/>
                <label><input type="checkbox" name="filename[]" value="field_day" />Field Day</label><br/>
                <label><input type="checkbox" name="filename[]" value="fwf" />FWF</label><br/>
                <label><input type="checkbox" name="filename[]" value="koyo" />Koyo</label><br/>
                <label><input type="checkbox" name="filename[]" value="med_organic" />Med Organic</label><br/>
                <label><input type="checkbox" name="filename[]" value="old_wessex" />Old Wessex</label><br/>
                <label><input type="checkbox" name="filename[]" value="rising_moon" />Rising Moon</label><br/>
                <!--
                <label><input type="checkbox" name="filename[]" value="rising_moon_new" />Rising Moon New</label><br/>
                -->
                <label><input type="checkbox" name="filename[]" value="harvest_bay" />Harvest Bay</label><br/>
                <label><input type="checkbox" name="filename[]" value="a_vogel" />A Vogel</label><br/>
                <label><input type="checkbox" name="filename[]" value="mt_vikos" />Mt Vikos</label><br/>
                <label><input type="checkbox" name="filename[]" value="tumaros" />Tumaros</label><br/>
                <label><input type="checkbox" name="filename[]" value="woodstock" />Woodstock</label><br/><br/>
                
                <input type="submit" value="Submit" class="FormSubmit" />
            </form>
            
                <!--
                <form action="./delete_sites.php" class="DeleteFiles" name="delete_files" method="post"></label><br/>
                    <input type="submit" value="Delete Files From Recent Run" class="FormSubmit" onclick="return confirm('All files will be deleted, Are you sure?')" />
                </form>
                -->
        </div>
        <div class="footer"></div>
    
    
    
</body>

</html>