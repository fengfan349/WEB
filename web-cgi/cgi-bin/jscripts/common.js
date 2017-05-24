
/* 进度条刷新 配合jquery使用 */
$(function(){
  
  var interval = setInterval(increment,10);
  var current = 0;
  var t=3;
  function increment()
  {
    current++;
	if(current == 100) 
	{   
		clearInterval(interval);
		$('h1').html("Configure Finished!"); 
		interval = setInterval(counttime,1000);
		function counttime()
		{ 
			$('#config_status').html("----Waiting "+t+"s for back----"); 
			if(t==0)
			{
				clearInterval(interval);
				location=document.referrer; 
			}
			t--;
		}
		
	}
    $('#counter').html(current+'%'); 
  }
});
/* 进度条刷新 */



/*导航栏*/

/*导航栏*/