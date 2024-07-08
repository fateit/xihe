<h1 style="color:red;letter-spacing: 1px;">v1.1.0 <b>用户手册</b></h1>


<a href="./../../README.md">[Back]</a><br>

>### <h1>目录</h1>


[<label style="font-size:20px;">1.资源</label>](#<h1>1.资源链接</h1>)    
[<label style="font-size:20px;">2.Topic详情</label>](#<h1>2.Topic详情</h1>)   
[<label style="font-size:20px;">3.Timestamp接口详情</label>](#<h1>3.Timestamp接口详情</h1>)   
[<label style="font-size:20px;">4.基于Esp32与fateit-xihe订阅读写标签值(mqtt)</label>](#<h1>4.边缘侧实例：基于Esp32与fateit-xihe订阅读写标签值(MQTT)</h1>)   
[<label style="font-size:20px;">5.基于Esp32与fateit-xihe读写标签值(http)</label>](#<h1>5.边缘侧实例：基于Esp32与fateit-xihe读写标签值(http)</h1>)   

<br>
<br>

>### <h1>1.资源链接</h1>

<b><h2>v1.1.0</h2></b> [<b style="font-size:18px;">资源链接</b>](https://github.com/fateit/xihe/releases)


<div style="font-size:16px;">

|  版本  |  语言|  日期|  链接|
|  ----  |----|----| ----   |
| v1.1.0 |zh_CN |2024-07| [下载](https://github.com/fateit/xihe/releases/download/v1.1.0/Fateit-Xihe.Gateway_User.Manual_v1.1.0_zh_CN.pdf) |
| v1.0.0 |zh_CN |2024-04| [下载](https://github.com/fateit/xihe/releases/download/v1.0.0/Fateit-Xihe.Gateway_User.Manual_v1.0.0_zh_CN.pdf) |

</div>

<br>
<br>

>### <h1>2.Topic详情</h1>


<div style="font-size:16px;">

|  来源  |  主题|  作用|  新增|  格式|  demo|描述|
|  ----  |----|----|----| ----   |----   |----   |
| 平台 |notify |变更推送|| Json |{"code":"PLC01_002",<br>"value":"2",<br>"dataType":"short",<br>"success":true,<br>"timestamp":1713589552287}|code：标签号<br>value：值<br>dataType：数据类型<br>success：是否可用<br>timestamp：时间戳
| 平台  |event 	   |  系统事件消息推送| <label style="color:red"> ✓ </label> |json|{"type":"EDGE_READ_ERROR",<br>"subject":"PLC01_001",<br>"message":"Label [PLC01_001] does not exist"}|type：事件类型[EDGE_READ_ERROR、EDGE_WRITE_ERROR]<br>subjuect：事件对象<br>message:具体消息
|  边缘 |edge/notify | 变更推送| <label style="color:red"> ✓ </label> |text|trueMAC002_0090short1713603499002null|successcodevaluedataTypetimestampmessage<br><label style="color:red">由特殊字符\b隔开</label>
|  边缘 |edge/event  | 系统事件消息推送| <label style="color:red"> ✓ </label> |text|EDGE_READ_ERRORPLC01_001Label [PLC01_001] does not exist|typesubjectmessage<br><label style="color:red">由特殊字符\b隔开</label>
|  边缘 |edge/w      | 写标签| <label style="color:red"> ✓ </label> |text| 发送主题：edge/w<label style="color:red">/LabelCode <br> 消息内容：要写入的值|
|  边缘 |edge/r      | 读标签| <label style="color:red"> ✓ </label> |text| 发送主题：edge/r<label style="color:red">/LabelCode <br> 消息内容：空|

</div>
<br>
<br>

>### <h1>3.Timestamp接口详情</h1>

<div style="font-size:16px;">

|  来源  |路径|  返回值|
|  ----  |----|----|
|平台|http://localhost:8376/fateit/comm/timestamp|json|
|边缘|http://localhost:8376/fateit/comm/edge/timestamp|json|
|方法|GET/POST
|参数|无


</div>
<br>
<br>

>### <h1>4.边缘侧实例：基于Esp32与fateit-xihe订阅读写标签值(MQTT)</h1>
<div style="font-size:18px;">

*  <b> esp32 需注意散热，如果温度过高，会导致单片机不稳定；如果Wifi网络不稳定，也会造成设备频繁掉线、或者网络调用错误等。</b>

|  工具  |  Arudion 2.0| [完整代码](./resource/3.wifi_mqtt_fateit_xihe_demo/3.wifi_mqtt_fateit_xihe_demo.ino)
|  ----  |----|----|
|<b>类库</b>|WiFi、PubSubClient
|<b>Modbus Slave</b>|[备份文件](./resource/Mbslave_data.mbs)


   1、连接Wifi  
   2、连接 fateit-xihe mqtt  
   3、订阅 topic  
   4、打印 label   
   5、写 label   
   6、读 label  
 
 1、连接Wifi ：setup()
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
2、连接 fateit-xihe mqtt ：setup()
```
  //init clientId
  clientId = getClientid();
  Serial.println(clientId);

  //init mqtt
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
```
3、订阅 topic ：reConnect()
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
4、5、6 打印写读标签：mqttCallback()
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

输出

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



>### <h1>5.边缘侧实例：基于Esp32与fateit-xihe读写标签值(http)</h1>
<div style="font-size:18px;">


|  工具  |  Arudion 2.0| [完整代码](./resource/4.wifi_http_fateie_xihe_demo/4.wifi_http_fateie_xihe_demo.ino)
|  ----  |----|----|
|<b>类库</b>|WiFi、HTTPClient、MD5Builder、ArduinoJson
|<b>Modbus Slave</b>|[备份文件](./resource/Mbslave_data.mbs)


   1、连接Wifi   
   2、写 label   
   3、读 label  
   
 1、连接Wifi ：setup()
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

 2、写 label  ：writeLabel()
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

 3、读 label  ：readLabel()
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

 输出
 
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
