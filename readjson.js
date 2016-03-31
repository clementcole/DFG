var jf = require('jsonfile')
var file = 'dictionary.json'
jf.readFile(file, function(err, jsonData){
	if(err) throw err,
		console.log("-------------Absolute Address------------");
	for (var i = 0; i< jsonData.length; ++i){
		console.log("absolute address: "+jsonData[i].absolute_address);
		console.log("instructions:"+jsonData[i].instructions);
		console.log("-----------------------------------------------------");
	}
});
