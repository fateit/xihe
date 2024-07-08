/*
 *  wifi_mqtt_fateit_xihe_demo
 *  1、connect wifi  
 *  2、connect fateit-xihe mqtt  
 *  3、sub topic  
 *  4、print label  
 *  5、write label  
 *  6、read label
 */

#include <WiFi.h>
#include <PubSubClient.h>
//wifi
const char* SSID = "your ssid";
const char* PASSWD = "your passwd";

//mqtt
char* mqttServer = "your fateit_xihe_mqtt_broker host";
int mqttPort = 1883;
char* mqttUser = "fateit";
char* mqttPassword = "fateit";

//connection
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


char* idPrex = "fateit.xihe";
String clientId;

const char* topic_notify = "edge/notify";
const char* topic_event = "edge/event";
char* topic_write = "edge/w/";
char* topic_read = "edge/r/";

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

  //init clientId
  clientId = getClientid();
  Serial.println(clientId);

  //init mqtt
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
}


void loop() {
  reConnect();
}


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


uint32_t getChipId() {
  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return chipId;
}

String getClientid() {
  uint32_t id = getChipId();
  return String(idPrex) + '.' + id;
}


//*******Fateit-xihe Message Class*******
class EventMessage {
private:
  String str;
  String type;
  String subject;
  String message;
  const String f = "";

public:
  EventMessage(String c) {
    str = c;
    String currStr = "";
    int index;
    int n = 0;
    do {
      index = str.indexOf(f);
      if (index != -1) {
        currStr = str.substring(0, index);
        str = str.substring(index + f.length(), str.length());
      } else {
        if (str.length() > 0) {
          currStr = str;
        } else {
          currStr = "";
        }
      }
      if (n == 0) {
        type = currStr;
      } else if (n == 1) {
        subject = currStr;
      } else if (n == 2) {
        message = currStr;
      }
      n++;
    } while (index >= 0);
  }

  String getType() {
    return type;
  }

  String getSubject() {
    return subject;
  }

  String getMessage() {
    return message;
  }
};


class LabelMessage {
private:
  String str;
  bool success = false;
  String code;
  String value;
  String dataType;
  String message;
  String timestamp;
  const String f = " ";

public:
  LabelMessage(String c) {
    str = c;
    if (str.startsWith("true")) {
      success = true;
      message = "OK";
    }

    String currStr = "";
    int index;
    int n = 0;
    do {
      index = str.indexOf(f);
      if (index != -1) {
        currStr = str.substring(0, index);
        str = str.substring(index + f.length(), str.length());
      } else {
        if (str.length() > 0) {
          currStr = str;
        } else {
          currStr = "";
        }
      }

      if (n == 1) {
        code = currStr;
      } else if (n == 2) {
        value = currStr;
      } else if (n == 3) {
        dataType = currStr;
      } else if (n == 4) {
        timestamp = currStr;
      } else if (n == 5) {
        message = currStr;
      }
      n++;
    } while (index >= 0);
  }

  bool isSuccess() {
    return success;
  }

  String getCode() {
    return code;
  }

  String getValue() {
    return value;
  }

  String getDataType() {
    return dataType;
  }

  String getTimestamp() {
    return timestamp;
  }

  String getMessage() {
    return message;
  }
};

//gen write topic by labelCode
char* gWt(char* labelCode) {
  return concat(topic_write, labelCode);
}
//gen read topic by labelCode
char* gRt(char* labelCode) {
  return concat(topic_read, labelCode);
}


char* concat(char* str1, char* str2) {
  int newLength = strlen(str1) + strlen(str2) + 1;
  char* newStr = (char*)malloc(newLength);
  if (newStr == NULL) {
    return NULL;
  }
  strcpy(newStr, str1);
  strcat(newStr, str2);
  return newStr;
}

//mqttCallback handler
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
  //Serial.println(content);
  
  //Serial.println("↓↓↓");
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
}