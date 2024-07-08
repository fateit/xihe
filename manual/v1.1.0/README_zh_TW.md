<h1 style="color:red;letter-spacing: 1px;">v1.1.0 <b>用戶手冊</b></h1>


<a href="./../../README_zh_TW.md">[Back]</a><br>

>### <h1>目錄</h1>
  

<a href="#c_1">1.資源</a><br>
<a href="#c_2">2.Topic詳情</a><br>
<a href="#c_3">3.Timestamp介面詳情</a><br>
<a href="#c_4">4.基於Esp32與fateit-xihe訂閱讀寫標籤值(mqtt)</a><br>
<a href="#c_5">5.基於Esp32與fateit-xihe讀寫標籤值(http)</a><br>

<br>
<br>

>### <h1>1.資源鏈接</h1>
<span id='c_1'></span>
<b><h2>v1.1.0</h2></b> [<b style="font-size:18px;">資源鏈接</b>](https://github.com/fateit/xihe/releases)


<div style="font-size:16px;">

|  版本  |  語言|  日期|  鏈接|
|  ----  |----|----| ----   |
| v1.1.0 |zh_CN |2024-07| [下載](https://github.com/fateit/xihe/releases/download/v1.1.0/Fateit-Xihe.Gateway_User.Manual_v1.1.0_zh_TW.pdf) |
| v1.0.0 |zh_CN |2024-04| [下載](https://github.com/fateit/xihe/releases/download/v1.0.0/Fateit-Xihe.Gateway_User.Manual_v1.0.0_zh_TW.pdf) |

</div>

<br>
<br>

>### <h1>2.Topic詳情</h1>
<span id='c_2'></span>

<div style="font-size:16px;">

|  來源  |  主題|  作用|  新增|  格式|  demo|描述|
|  ----  |----|----|----| ----   |----   |----   |
| 平臺 |notify |變更推送|| Json |{"code":"PLC01_002",<br>"value":"2",<br>"dataType":"short",<br>"success":true,<br>"timestamp":1713589552287}|code：標籤號<br>value：值<br>dataType：數據類型<br>success：是否可用<br>timestamp：時間戳
| 平臺  |event 	   |  系統事件消息推送| <label style="color:red"> ✓ </label> |json|{"type":"EDGE_READ_ERROR",<br>"subject":"PLC01_001",<br>"message":"Label [PLC01_001] does not exist"}|type：事件類型[EDGE_READ_ERROR、EDGE_WRITE_ERROR]<br>subjuect：事件對象<br>message:具體消息
|  邊緣 |edge/notify | 變更推送| <label style="color:red"> ✓ </label> |text|trueMAC002_0090short1713603499002null|successcodevaluedataTypetimestampmessage<br><label style="color:red">由特殊字元\b隔開</label>
|  邊緣 |edge/event  | 系統事件消息推送| <label style="color:red"> ✓ </label> |text|EDGE_READ_ERRORPLC01_001Label [PLC01_001] does not exist|typesubjectmessage<br><label style="color:red">由特殊字元\b隔開</label>
|  邊緣 |edge/w      | 寫標籤| <label style="color:red"> ✓ </label> |text| 發送主題：edge/w<label style="color:red">/LabelCode <br> 消息內容：要寫入的值|
|  邊緣 |edge/r      | 讀標籤| <label style="color:red"> ✓ </label> |text| 發送主題：edge/r<label style="color:red">/LabelCode <br> 消息內容：空|

</div>
<br>
<br>

>### <h1>3.Timestamp介面詳情</h1>
<span id='c_3'></span>
<div style="font-size:16px;">

|  來源  |路徑|  返回值|
|  ----  |----|----|
|平臺|http://localhost:8376/fateit/comm/timestamp|json|
|邊緣|http://localhost:8376/fateit/comm/edge/timestamp|json|
|方法|GET/POST
|參數|無


</div>
<br>
<br>

>### <h1>4.邊緣側實例：基於Esp32與fateit-xihe訂閱讀寫標籤值(MQTT)</h1>
<span id='c_4'></span>
<div style="font-size:18px;">

*  <b> esp32 需注意散熱，如果溫度過高，會導致單片機不穩定；如果Wifi網路不穩定，也會造成設備頻繁掉線、或者網路調用錯誤等。</b>

|  工具  |  Arudion 2.0| [完整代碼](./resource/3.wifi_mqtt_fateit_xihe_demo/3.wifi_mqtt_fateit_xihe_demo.ino)
|  ----  |----|----|
|<b>類庫</b>|WiFi、PubSubClient
|<b>Modbus Slave</b>|[備份檔](./resource/Mbslave_data.mbs)


   1、連接Wifi  
   2、連接 fateit-xihe mqtt  
   3、訂閱 topic  
   4、列印 label   
   5、寫 label   
   6、讀 label  
 
 1、連接Wifi ：setup()
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
2、連接 fateit-xihe mqtt ：setup()
```
  //init clientId
  clientId = getClientid();
  Serial.println(clientId);

  //init mqtt
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
```
3、訂閱 topic ：reConnect()
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
4、5、6 列印寫讀標籤：mqttCallback()
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

輸出

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



>### <h1>5.邊緣側實例：基於Esp32與fateit-xihe讀寫標籤值(http)</h1>
<span id='c_5'></span>
<div style="font-size:18px;">


|  工具  |  Arudion 2.0| [完整代碼](./resource/4.wifi_http_fateie_xihe_demo/4.wifi_http_fateie_xihe_demo.ino)
|  ----  |----|----|
|<b>類庫</b>|WiFi、HTTPClient、MD5Builder、ArduinoJson
|<b>Modbus Slave</b>|[備份檔](./resource/Mbslave_data.mbs)


   1、連接Wifi   
   2、寫 label   
   3、讀 label  
   
 1、連接Wifi ：setup()
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

 2、寫 label  ：writeLabel()
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

 3、讀 label  ：readLabel()
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

 輸出
 
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
