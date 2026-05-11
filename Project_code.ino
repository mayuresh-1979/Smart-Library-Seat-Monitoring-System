/*
========================================================
LIBRARY SEAT MONITORING SYSTEM
ESP32 + IR SENSOR + FSR + WEB SERVER
========================================================

FEATURES:
✔ WiFi Dashboard
✔ Chrome Monitoring
✔ Live Seat Status
✔ LED Indication
✔ Attractive UI
✔ Stable WebServer Version

========================================================
CONNECTIONS

IR SENSOR:
VCC -> 3V3
GND -> GND
OUT -> D4

FSR:
One end -> 3V3
Other end -> D34
10k resistor from D34 -> GND

RED LED:
D5 -> Resistor -> LED +
LED - -> GND

GREEN LED:
D19 -> Resistor -> LED +
LED - -> GND

========================================================
IMPORTANT:
USE ESP32 BOARD VERSION = 2.0.17
========================================================
*/

#include <WiFi.h>
#include <WebServer.h>

// ======================================================
// WIFI DETAILS
// ======================================================
const char* ssid = "______";
const char* password = "______";

// ======================================================
// PIN DEFINITIONS
// ======================================================
#define IR_SENSOR_PIN 4
#define FSR_PIN 34

#define RED_LED 5
#define GREEN_LED 19

// ======================================================
// VARIABLES
// ======================================================
int fsrValue = 0;
int irValue = 0;

int fsrThreshold = 1200;

String seatStatus = "AVAILABLE";

// ======================================================
// CREATE WEB SERVER
// ======================================================
WebServer server(80);

// ======================================================
// HTML WEBPAGE
// ======================================================
String webpage = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<title>Library Seat Monitoring</title>

<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

body{
    margin:0;
    padding:0;
    font-family: Arial;
    background: linear-gradient(to right,#141E30,#243B55);
    color:white;
    text-align:center;
}

.container{
    margin-top:50px;
}

.card{
    width:350px;
    margin:auto;
    background:rgba(255,255,255,0.1);
    padding:30px;
    border-radius:20px;
    box-shadow:0px 0px 20px rgba(0,0,0,0.4);
}

h1{
    font-size:30px;
}

.status{
    font-size:28px;
    font-weight:bold;
    margin-top:20px;
}

.data{
    font-size:22px;
    margin-top:20px;
}

.circle{
    width:35px;
    height:35px;
    border-radius:50%;
    margin:auto;
    margin-top:25px;
}

</style>

</head>

<body>

<div class="container">

<div class="card">

<h1>Library Seat Monitoring</h1>

<div class="status" id="status">
Loading...
</div>

<div class="data">
IR Sensor : <span id="ir">--</span>
</div>

<div class="data">
FSR Value : <span id="fsr">--</span>
</div>

<div class="circle" id="circle"></div>

</div>

</div>

<script>

function updateData(){

fetch('/data')

.then(response => response.json())

.then(data => {

document.getElementById('status').innerHTML = data.status;

document.getElementById('ir').innerHTML = data.ir;

document.getElementById('fsr').innerHTML = data.fsr;

if(data.status == "OCCUPIED"){

document.getElementById('status').style.color = "red";

document.getElementById('circle').style.background = "red";

document.getElementById('circle').style.boxShadow = "0 0 20px red";

}

else{

document.getElementById('status').style.color = "#00ff99";

document.getElementById('circle').style.background = "#00ff99";

document.getElementById('circle').style.boxShadow = "0 0 20px #00ff99";

}

});

}

setInterval(updateData,1000);

</script>

</body>
</html>

)rawliteral";

// ======================================================
// HANDLE ROOT PAGE
// ======================================================
void handleRoot()
{
    server.send(200, "text/html", webpage);
}

// ======================================================
// HANDLE SENSOR DATA
// ======================================================
void handleData()
{
    String json = "{";

    json += "\"status\":\"" + seatStatus + "\",";
    json += "\"ir\":\"" + String(irValue) + "\",";
    json += "\"fsr\":\"" + String(fsrValue) + "\"";

    json += "}";

    server.send(200, "application/json", json);
}

// ======================================================
// SETUP
// ======================================================
void setup()
{
    Serial.begin(115200);

    pinMode(IR_SENSOR_PIN, INPUT);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    // ==================================================
    // CONNECT TO WIFI
    // ==================================================
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");

    int timeout = 0;

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        Serial.print(".");

        timeout++;

        // Timeout after 30 tries
        if(timeout > 30)
        {
            Serial.println("\nWiFi Connection Failed!");

            Serial.println("Check:");
            Serial.println("1. WiFi Name");
            Serial.println("2. Password");
            Serial.println("3. Hotspot should be 2.4 GHz");

            return;
        }
    }

    Serial.println("\nWiFi Connected Successfully!");

    // ==================================================
    // PRINT IP ADDRESS
    // ==================================================
    Serial.print("Open Chrome and enter: http://");

    Serial.println(WiFi.localIP());

    // ==================================================
    // WEB SERVER ROUTES
    // ==================================================
    server.on("/", handleRoot);

    server.on("/data", handleData);

    // ==================================================
    // START SERVER
    // ==================================================
    server.begin();

    Serial.println("Web Server Started!");
}

// ======================================================
// LOOP
// ======================================================
void loop()
{
    server.handleClient();

    // Read Sensors
    irValue = digitalRead(IR_SENSOR_PIN);

    fsrValue = analogRead(FSR_PIN);

    // Detection Logic
    bool irDetected = (irValue == LOW);

    bool pressureDetected = (fsrValue > fsrThreshold);

    // Seat Occupied
    if(irDetected && pressureDetected)
    {
        seatStatus = "OCCUPIED";

        digitalWrite(RED_LED, HIGH);

        digitalWrite(GREEN_LED, LOW);
    }

    // Seat Available
    else
    {
        seatStatus = "AVAILABLE";

        digitalWrite(RED_LED, LOW);

        digitalWrite(GREEN_LED, HIGH);
    }

    delay(200);
}