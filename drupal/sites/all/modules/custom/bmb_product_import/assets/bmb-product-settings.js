(function ($) {
  $(document).ready(function(){
   
    $('button').click(function(e){
      var textfield_id = $(this).attr('mg');
      if(!textfield_id) return;
      
      console.log(textfield_id);
      var textfield_val = $("#" + textfield_id).val();
      if(!textfield_val) {
        alert('URL information must be entered for this site!');
        $("#" + textfield_id).css({'background-color' : '#ffcccc'}).focus();
        e.stopPropagation();
        e.preventDefault(); 
      } 
    });
    
    /*
    $('#edit-pws :input').focus(function(e){
      $(this).css({'background-color' : '#ffcccc'});
    });
    */

  }); // doc.ready
}(jQuery));