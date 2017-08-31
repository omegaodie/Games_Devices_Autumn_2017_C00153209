var GameData, Plists,  loaded;
function levelLoader() 
{
    var _data_str = 'data.json';
	loadJSON(_data_str, function(response) 
    {


  		// Parse JSON string into object
		GameData = JSON.parse(response);
        var menu_plist_src = GameData.GeneralMenu.src_img + ".json";

		loaded = false;
        loadJSON(menu_plist_src, function (responseText) 
        {
            Plists = JSON.parse(responseText);
            loaded = true;
        });
 	});
}


function loadJSON( filePath, callback) {   

    var xobj = new XMLHttpRequest();
        xobj.overrideMimeType("application/json");
        xobj.open("GET", filePath, true); // Replace 'my_data' with the path to your file
        xobj.onload = function () {
            callback(xobj.responseText);
    };
    xobj.send(null);  
 }