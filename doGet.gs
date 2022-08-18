var ss = SpreadsheetApp.openById('File_ID');
var sheet = ss.getSheetByName('Sheet_NAME');

function doGet(e) {
  //----------------------------------------------------------------------------------
  //write_google_sheet() function in esp32 sketch, is send data to this code block
  //----------------------------------------------------------------------------------
  //get data from ESP32
  if (e.parameters == 'undefined') {
    return ContentService.createTextOutput("Received data is undefined");
  }
  //----------------------------------------------------------------------------------
  var dateTime = new Date();
  temp    = e.parameters.temp;
  hum_ext = e.parameters.hum_ext;
  z_water = e.parameters.z_water;
  hum1    = e.parameters.hum1;
  hum2    = e.parameters.hum2;

  //----------------------------------------------------------------------------------
  var nextRow = sheet.getLastRow() + 1;
  sheet.getRange("A" + nextRow).setValue(dateTime);
  sheet.getRange("B" + nextRow).setValue(temp);
  sheet.getRange("C" + nextRow).setValue(hum_ext);
  sheet.getRange("D" + nextRow).setValue(z_water);
  sheet.getRange("E" + nextRow).setValue(hum1);
  sheet.getRange("F" + nextRow).setValue(hum2);

  //----------------------------------------------------------------------------------

  //returns response back to ESP32
  return ContentService.createTextOutput("Status Updated in Google Sheet");
  //----------------------------------------------------------------------------------
}



