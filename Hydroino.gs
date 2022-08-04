#https://www.youtube.com/watch?v=hxK3XJ0KfRg&ab_channel=paoloaliverti

function doGet(e) {
  var temp = e.parameter.temp;
  var hum = e.parameter.hum;
  var z = e.parameter.z;

  Logger.log(temp);
  Logger.log(hum);
  Logger.log(z);
  
  logToSpreadSheet(temp,hum,z);

  var ret = {status: 'success'};
  return ContentService.createTextOutput(JSON.stringify(ret)).setMimeType(ContentService.MimeType.JSON);
}


function logToSpreadSheet(temp,hum,z){
  var ss = SpreadsheetApp.openById('1wa5WQvOVNzkMFvrpGKXqmOqHA2LjR4fi-gp5h8Q51uE');
  var foglio = ss.getSheetByName('arduino');
  foglio.appendRow([new Date(), temp, hum, z]);
}