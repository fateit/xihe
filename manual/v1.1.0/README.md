<h1 style="color:red;letter-spacing: 1px;">v1.1.0 <b>User Manual</b></h1>


<a href="./../../README.md">[Back]</a><br>


>### <h1>Catalogue</h1>


[<label style="font-size:20px;">1.Resource</label>](#<h1>1.Resource&nbsp;Link</h1>)    
[<label style="font-size:20px;">2.Topic&nbsp;Details</label>](#<h1>2.Topic&nbsp;details</h1>)   
[<label style="font-size:20px;">3.Timestamp Interface details</label>](#<h1>3.Timestamp&nbsp;Interface&nbsp;details</h1>)   
[<label style="font-size:20px;">4.Read ,write or Subscribe label based on Esp32 and fateit-xihe(mqtt)</label>](#<h1>4.Edge&nbsp;side&nbsp;example：Read&nbsp;,write&nbsp;or&nbsp;Subscribe&nbsp;label&nbsp;based&nbsp;on&nbsp;Esp32&nbsp;and&nbsp;fateit-xihe(MQTT)</h1>)   
[<label style="font-size:20px;">5.Read and write label based on Esp32 and fateit-xihe(http)</label>](#<h1>5.Edge&nbsp;side&nbsp;example：Read&nbsp;and&nbsp;write&nbsp;label&nbsp;based&nbsp;on&nbsp;Esp32&nbsp;and&nbsp;fateit-xihe(http)</h1>)   

<br>
<br>

>### <h1>1.Resource Link</h1>

<b><h2>v1.1.0</h2></b> [<b style="font-size:18px;">Resource Link</b>](https://github.com/fateit/xihe/releases)


<div style="font-size:16px;">

| Version | Language | Date | Link |
|  ----  |----|----| ----   |
| v1.1.0 |en |2024-07| [Download](https://github.com/fateit/xihe/releases/download/v1.1.0/Fateit-Xihe.Gateway_User.Manual_v1.1.0_en_US.pdf) |
| v1.0.0 |en |2024-04| [Download](https://github.com/fateit/xihe/releases/download/v1.0.0/Fateit-Xihe.Gateway_User.Manual_v1.0.0_en_US.pdf) |

</div>

<br>
<br>

>### <h1>2.Topic details</h1>


<div style="font-size:16px;">

| Source | role | function | new | format | demo | description |
|  ----  |----|----|----| ----   |----   |----   |
| Platform |notify |Change push|| Json |{"code":"PLC01_002",<br>"value":"2",<br>"dataType":"short",<br>"success":true,<br>"timestamp":1713589552287}|code：label code<br>value：label value<br>dataType<br>success：Is available<br>timestamp
| Platform  |event 	   |  System event message push| <label style="color:red"> ✓ </label> |json|{"type":"EDGE_READ_ERROR",<br>"subject":"PLC01_001",<br>"message":"Label [PLC01_001] does not exist"}|type：Event type[EDGE_READ_ERROR、EDGE_WRITE_ERROR]<br>subjuect：Event subjuect<br>message:message
|  Edge |edge/notify | Change push| <label style="color:red"> ✓ </label> |text|trueMAC002_0090short1713603499002null|successcodevaluedataTypetimestampmessage<br><label style="color:red">split by the special char \b</label>
|  Edge |edge/event  | System event message push| <label style="color:red"> ✓ </label> |text|EDGE_READ_ERRORPLC01_001Label [PLC01_001] does not exist|typesubjectmessage<br><label style="color:red">split by the special char \b</label>
|  Edge |edge/w      | Write Label| <label style="color:red"> ✓ </label> |text| Topic：edge/w<label style="color:red">/LabelCode <br> content：label value|
|  Edge |edge/r      | Read Label| <label style="color:red"> ✓ </label> |text| Topic：edge/r<label style="color:red">/LabelCode <br> content：None|

</div>
<br>
<br>

>### <h1>3.Timestamp Interface details</h1>

<div style="font-size:16px;">

| Source | path | Result |
|  ----  |----|----|
|Platform|http://localhost:8376/fateit/comm/timestamp|json|
|Edge|http://localhost:8376/fateit/comm/edge/timestamp|json|
|Method|GET/POST
|Param|None


</div>
<br>
<br>

>### <h1>4.Edge side example：Read ,write or Subscribe label based on Esp32 and fateit-xihe(MQTT)</h1>
<div style="font-size:18px;">

*  <b> esp32 Attention should be paid to heat dissipation. If the temperature is too high, microchip instability, and WIfi network instability will cause frequent equipment disconnection or network calling errors.</b>

|  Tool  |  Arudion 2.0| [Code](./resource/3.wifi_mqtt_fateit_xihe_demo/3.wifi_mqtt_fateit_xihe_demo.ino)
|  ----  |----|----|
|<b>Libraries</b>|WiFi、PubSubClient
|<b>Modbus Slave</b>|[backup file](./resource/Mbslave_data.mbs)


   1、Connect Wifi  
   2、Connect fateit-xihe mqtt  
   3、Sub topic  
   4、Print label   
   5、Write label   
   6、Read label  
 
 1、Connect Wifi ：setup()
 ```
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

```
2、Connect fateit-xihe mqtt ：setup()
```
  //init clientId
  clientId = getClientid();
  Serial.println(clientId);

  //init mqtt
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
```
3、Sub topic ：reConnect()
```
void reConnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("mqtt connected");
      //resubscribe
      mqttClient.subscribe(topic_notify);
      mqttClient.subscribe(topic_event);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

  mqttClient.loop();
}
```
4、5、6 print,write and read Label：mqttCallback()
```
 void mqttCallback(char* topic, byte* payload, unsigned int length) {
  
  Serial.println("==========");

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  if (length <= 0) {
    return;
  }

  String content = "";
  Serial.print("recived msg:");
  for (int i = 0; i < length; i++) {
    content.concat(String((char)payload[i]));
  }
  Serial.println(content);
  
  Serial.println("↓↓↓");
  // edge/notify
  if (strcmp(topic, topic_notify) == 0) {
    LabelMessage lm(content);

    Serial.print("suc:");
    Serial.println(lm.isSuccess());
    Serial.print("code:");
    Serial.println(lm.getCode());
    Serial.print("value:");
    Serial.println(lm.getValue());
    Serial.print("dataType:");
    Serial.println(lm.getDataType());
    Serial.print("timestamp:");
    Serial.println(lm.getTimestamp());
    Serial.print("msg:");
    Serial.println(lm.getMessage());

    if (lm.getCode().endsWith("PLC01_002")) {
      //write label
      mqttClient.publish(gWt("PLC01_1000"), "Hi,Fateit");
      delay(1000);
      //read label
      mqttClient.publish(gRt("PLC01_1000"), "");
    }
  } else if (strcmp(topic, topic_event) == 0) {  // edge/event
    EventMessage em(content);

    Serial.print("type:");
    Serial.println(em.getType());
    Serial.print("subject:");
    Serial.println(em.getSubject());
    Serial.print("msg:");
    Serial.println(em.getMessage());
  }
```

Output

```
Connecting to WIFI_FATEIT
.
WiFi connected
IP address: 
192.168.10.142
fateit.xihe.1052776
Attempting MQTT connection...mqtt connected
==========
Message arrived [edge/notify] 
recived msg:suc:1
code:PLC01_002
value:1
dataType:short
timestamp:1714189632192
msg:null
==========
Message arrived [edge/notify] 
recived msg:suc:1
code:PLC01_1000
value:Hi,Fateit 
dataType:string
timestamp:1714189633245
msg:null
```


</div>
<br>
<br>



>### <h1>5.Edge side example：Read and write label based on Esp32 and fateit-xihe(http)</h1>
<div style="font-size:18px;">


|  Tool  |  Arudion 2.0| [Code](./resource/4.wifi_http_fateie_xihe_demo/4.wifi_http_fateie_xihe_demo.ino)
|  ----  |----|----|
|<b>Libraries</b>|WiFi、HTTPClient、MD5Builder、ArduinoJson
|<b>Modbus Slave</b>|[backup file](./resource/Mbslave_data.mbs)


   1、Connect Wifi   
   2、write label   
   3、read label  
   
 1、Connect Wifi ：setup()
 ```
 void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
 ```

 2、write label  ：writeLabel()
 ```
 String writeLabel(String code, String value) {

  HttpSignature hs(KEY_SAFE, timestamp_, timestamp_);

  HTTPClient http;

  String payload = "{\"code\":\"" + code + "\",\"value\":\"" + value + "\"}";

  http.begin(PATH_XIHE + URL_WRITE);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("nonce", hs.getNonce());
  http.addHeader("timestamp", hs.getTimestamp());
  http.addHeader("signature", hs.getSignature());

  int httpCode = http.POST(payload);

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      return response;
    }
  }
  http.end();
  Serial.printf("writeLabel  %s failed, error: %s\n", code, http.errorToString(httpCode).c_str());
  return "";
}
```

 3、read label  ：readLabel()
 ```
 String readLabel(String labelCode) {

  HttpSignature hs(KEY_SAFE, timestamp_, timestamp_);
  HTTPClient http;
  http.begin(PATH_XIHE + URL_READ + labelCode);

  http.addHeader("nonce", hs.getNonce());
  http.addHeader("timestamp", hs.getTimestamp());
  http.addHeader("signature", hs.getSignature());

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      return response;
    }
  }
  http.end();

  Serial.printf("readLabel labelCode %s failed, error: %s\n", labelCode, http.errorToString(httpCode).c_str());
  return "";
}
 ```
4、Loop
 ```
void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {

    timestamp_ = getTs();
    String lblCode = "PLC01_002";

    Serial.println();
    Serial.println();
    if (timestamp_ != "") {
      String wirteValue = String(random(100));
      String result = writeLabel(lblCode, wirteValue);
      if (result != "") {
        Serial.printf("writeLabel  %s -> %s \n", lblCode, wirteValue);
        JsonResult rs(result);
        Serial.print("success:");
        Serial.println(rs.getSuccess());
      }

      delay(2000);
      Serial.println();
      
      result = readLabel(lblCode);
      if (result != "") {
        JsonResult rs(result);
        if (rs.getSuccess()) {
          Serial.printf("readLabel  %s success \n", lblCode);
          Serial.print("success:");
          Serial.println(rs.getSuccess());
          Serial.print("msg:");
          Serial.println(rs.getMessage());
          if (rs.getSuccess()) {
            LabelValue lv = rs.obj2LabelValue();
            Serial.print("label code:");
            Serial.println(lv.getCode());
            Serial.print("label value:");
            Serial.println(lv.getValue());
            Serial.print("label status:");
            Serial.println(lv.getSuccess());
            Serial.print("label dataType:");
            Serial.println(lv.getDataType());
            Serial.print("label timestamp:");
            Serial.println(lv.getTimestamp());
          }

        } else {
          Serial.printf("readLabel  %s error", lblCode);
        }
      }
    }
  }

  delay(5000);
}
 ```

 Output
 
```
Connecting to WIFI-FATEIT
.............................
WiFi connected
IP address: 
192.168.10.142


writeLabel  PLC01_002 -> 85 
success:1

readLabel  PLC01_002 success 
success:1
msg:success
label code:PLC01_002
label value:85
label status:1
label dataType:short
label timestamp:


writeLabel  PLC01_002 -> 51 
success:1

readLabel  PLC01_002 success 
success:1
msg:success
label code:PLC01_002
label value:51
label status:1
label dataType:short
label timestamp:

```

</div>
