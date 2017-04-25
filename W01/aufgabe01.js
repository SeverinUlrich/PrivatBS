var fs = require('fs');
var colour = require('chalk');
fs.readFile('staedte.json', 'utf8', function(err,data)
{
  if (err) throw err;
  var staedteData = JSON.parse(data);
  staedteData.cities.sort(function (a,b) {
    if (a.population > b.population) {
      return 1;
    }
    if (a.population < b.population) {
      return -1;
    }
    return 0;
  });
  fs.writeFile(__dirname + "/staedte_sortiert.json", JSON.stringify(staedteData.cities), function(err, data){
    if (err){
      console.log(err);
      return;
    }
    console.log("Datei gespeichert!");
    });
    for(var i = 0; i < staedteData.cities.length; i++)
    {
    console.log(colour.red("Name:"+staedteData.cities[i].name));
    console.log(colour.yellow("Country:"+staedteData.cities[i].country));
    console.log(colour.green("Population:"+staedteData.cities[i].population));
    console.log("---------------------------------");
    }
});
