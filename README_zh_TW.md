# xihe-iot-gateway

<div style="font-size:18px;">
Industrial Edge IoT Gateway

[English](./README.md) [中文简体](./README_zh_CN.md) [中文繁體](./README_zh_TW.md) 

</div>

>### <h1>目録</h1>
[<b style="font-size:24px;">1.介绍</b>](#<h1>1.介紹</h1>)    
[<b style="font-size:24px;">2.更新日志</b>](#<h1>2.更新日志</h1>)   



>### <h1>1.介紹</h1>


<center><h1><b>Fateit-Xihe 工業邊緣物聯網關</b></h1></center><br>

<h3 style="color:red;letter-spacing: 1px;">*更多詳細資訊請查看<b>用戶手冊</b>，附錄有基於Raspi 4b的應用實例。</h3><br>

![avatar](images/main-zh_TW.png)

<div style="letter-spacing: 1px;">
&nbsp;&nbsp;&nbsp;&nbsp;Fateit-Xihe 是一款免費的工業邊緣物聯網網關，簡稱羲和物聯網關，可跨平臺運行，功能豐富，運行穩定可靠且易於使用，支持不同種類的設備（PLC、半導體、物聯網設備），通過MQTT推送變化的數據，且提供基於http的羽量級數據讀寫接口。<br>
&nbsp;&nbsp;&nbsp;&nbsp;降低設備互聯門檻，打通<b>設備交互</b>、<b>數據採集</b>、<b>數據落地</b>的難點，從而助力中小微企業實現數位化、智能化升級的轉型。<br>
為企業提升生產、品質效益，從而提高企業整體的競爭力。<br>  
<b>主要功能：</b><br>  
1、內置MQTT v3 Broker：原生<b>高性能</b>Mqtt服務端，支持:tcp(1883)、websocket(8083)，無需部署另外的MQTT Broker。<br>
2、支持的驅動：<b>Modbus(tcp)</b>、<b>半導體協議:SECS/GEM(hsms)</b>、<b>OPC UA</b>、<b>Iot Message(mqtt)</b>，後續會按計畫擴展。<br>
3、數據基於事件變化推送到MQTT。<br>
4、斷線重連、設備啟動自動連接。<br>
5、獨特記憶體<b>數據結構</b>設計，對於多點位讀取性能更強。<br>
6、<b>一鍵啟動</b>，簡易線上配置拆箱即用，低運維成本，拒絕繁瑣配置。<br>
7、<b>支持消息Cassandra、Kafka推送，方便進行大數據存儲、傳輸以及分析[開啟會增加額外的資源開銷]</b><br>
8、<b>Fateit 富有生命力的數位化生態圈支持</b><br>
9、適合運行在<b>邊緣端</b>、也適合運行在<b>伺服器</b>上，滿足用戶各種實際場景。<br>
&nbsp;&nbsp;&nbsp;&nbsp;隱藏設備協議對接的複雜性，助力設備對接的快速落地，提供簡化、統一化、通用化、超前化的數據對接方式與數據結構，讓用戶更專注於上層架構，聚焦自身核心業務，為企業的發展提速。<br><br><br>
</div>




>### <h1>2.更新日誌</h1>


<center><h1><b>2.更新日誌</b></h1></center><br>

<h3><label style="color:red;letter-spacing: 1px;">*更多詳細資訊請查看<b>用戶手冊</b>，附錄有基於Raspi 4b的應用實例。</label></h3><br>
<div style="font-size:16px;">

|  Version   |  Date  |  Notes  | Details
|  ----  |----| ----   | ---- | ---- 
| V1.1.0  |2024-07| <label style="color:red">1.增加Mqtt協議對標籤讀寫的支持，以及系統事件推送<br>2.增加開放的獲取時間戳介面：timestamp</label>|[v1.1.0](./manual/v1.1.0/README_zh_TW.md)
| v1.0.0  |2024-04| Release |[v1.0.0](./manual/v1.0.0/README.md)

</div>