/*
 *  wifi_http_fateit_xihe_demo
 *  1、connect wifi  
 *  2、write label  
 *  3、read label
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <MD5Builder.h>
#include <ArduinoJson.h>

//wifi
const char* SSID = "your ssid";
const char* PASSWD = "your passwd";

const String PATH_XIHE = "http://192.168.10.204:8376/";
const String URL_TS = "fateit/comm/edge/timestamp";
const String URL_TS2 = "fateit/comm/timestamp";
const String URL_READ = "fateit/open/plc/readFast?code=";
const String URL_WRITE = "fateit/open/plc/write";
const String KEY_SAFE = "fateit";

String timestamp_;

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



String str2md5(String str) {
  MD5Builder md5;
  md5.begin();
  md5.add(str);
  md5.calculate();
  return md5.toString();
}

//*******Fateit-xihe Http Class*******
class HttpSignature {
private:
  String key;
  String timestamp;
  String nonce;
  String signature;

public:
  HttpSignature(String key, String ts, String nc) {
    key = key;
    timestamp = ts;
    nonce = nc;
    signature = str2md5(key + timestamp + nonce);
  }

  String getKey() {
    return key;
  }
  String getTimestamp() {
    return timestamp;
  }
  String getNonce() {
    return nonce;
  }
  String getSignature() {
    return signature;
  }
};

class LabelValue {
private:
  bool success;
  String code;
  String value;
  String dataType;
  String timestamp;
public:
  LabelValue(String json) {
    StaticJsonDocument<192> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F(" LabelValue deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    JsonObject j_obj = doc["obj"];

    const char* d_code = j_obj["code"];
    const char* d_value = j_obj["value"];
    const char* d_dataType = j_obj["dataType"];
    const char* d_timestamp = doc["timestamp"];
    code = d_code;
    value = d_value;
    dataType = d_dataType;
    success = doc["success"];
    timestamp=d_timestamp;
  }
  LabelValue(String c, String v, bool s) {
    code = c;
    value = v;
    success = s;
  }

  bool getSuccess() {
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
};

class JsonResult {
private:
  bool success;
  String message;
  String obj;
  String source;
public:
  JsonResult(String json) {
    source = json;
    StaticJsonDocument<192> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    success = doc["success"];
    const char* d_message = doc["message"];
    const char* d_obj = doc["obj"];
    message = d_message;
    obj = d_obj;
  }

  JsonResult(bool suc, String msg) {
    success = suc;
    message = msg;
  }

  bool getSuccess() {
    return success;
  }

  String getMessage() {
    return message;
  }

  LabelValue obj2LabelValue() {
    if (success) {
      LabelValue lv(source);
      return lv;
    }
    LabelValue nl("", "", false);
    return nl;
  }
};



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

String getTs() {
  HTTPClient http;

  http.begin(PATH_XIHE + URL_TS);

  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      return payload;
    }
  }
  Serial.printf("GET timestamp failed, error: %s\n", http.errorToString(httpCode).c_str());
  http.end();
  return "";
}