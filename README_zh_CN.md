# xihe-iot-gateway

<div style="font-size:18px;">
Industrial Edge IoT Gateway

[English](./README.md) [中文简体](./README_zh_CN.md) [中文繁體](./README_zh_TW.md) 

</div>

>### <h1>目录</h1>
<a href="#c_Introduction">1.介绍</a><br>
<a href="#c_UpdateNotes">2.更新日志</a>



>### <h1>介绍</h1>
<span id='c_Introduction'></span>

<center><h1><b>Fateit-Xihe 工业边缘物联网关</b></h1></center><br>

<h3 style="color:red;letter-spacing: 1px;">*更多详细信息请查看<b>用户手册</b>，附录有基于Raspi 4b的应用实例。</h3><br>

![avatar](images/main-zh_CN.png)

<div style="letter-spacing: 1px;">
&nbsp;&nbsp;&nbsp;&nbsp;Fateit-Xihe 是一款免费的工业边缘物联网网关，简称羲和物联网关，可跨平台运行，功能丰富，运行稳定可靠且易于使用，支持不同种类的设备（PLC、半导体、物联网设备），通过MQTT推送变化的数据，且提供基于http的轻量级数据读写接口。<br>
&nbsp;&nbsp;&nbsp;&nbsp;降低设备互联门槛，打通<b>设备交互</b>、<b>数据采集</b>、<b>数据落地</b>的难点，从而助力中小微企业实现数字化、智能化升级的转型。<br>
为企业提升生产、质量效益，从而提高企业整体的竞争力。<br>  
<b>主要功能：</b><br>  
1、内置MQTT v3 Broker：原生<b>高性能</b>Mqtt服务端，支持:tcp(1883)、websocket(8083)，无需部署另外的MQTT Broker。<br>
2、支持的驱动：<b>Modbus(tcp)</b>、<b>半导体协议:SECS/GEM(hsms)</b>、<b>OPC UA</b>、<b>Iot Message(mqtt)</b>，后续会按计划扩展。<br>
3、数据基于事件变化推送到MQTT。<br>
4、断线重连、设备启动自动连接。<br>
5、独特内存<b>数据结构</b>设计，对于多点位读取性能更强。<br>
6、<b>一键启动</b>，简易在线配置拆箱即用，低运维成本，拒绝繁琐配置。<br>
7、<b>支持消息Cassandra、Kafka推送，方便进行大数据存储、传输以及分析[开启会增加额外的资源开销]</b><br>
8、<b>Fateit 富有生命力的数字化生态圈支持</b><br>
9、适合运行在<b>边缘端</b>、也适合运行在<b>服务器</b>上，满足用户各种实际场景。<br>
&nbsp;&nbsp;&nbsp;&nbsp;隐藏设备协议对接的复杂性，助力设备对接的快速落地，提供简化、统一化、通用化、超前化的数据对接方式与数据结构，让用户更专注于上层架构，聚焦自身核心业务，为企业的发展提速。<br><br><br>
</div>




>### <h1>2.更新日志</h1>
<span id='c_UpdateNotes'></span>
<h3 style="color:red;letter-spacing: 1px;">*更多详细信息请查看<b>用户手册</b>，附录有基于Raspi 4b的应用实例。</h3><br>
<div style="font-size:16px;">

|Version|Date|Notes|Details
|-|-|-|-
| V1.1.0  |2024-07| <b>1.增加Mqtt协议对标签读写的支持，以及系统事件推送<br>2.增加开放的获取时间戳接口：timestamp</b>|[v1.1.0](./manual/v1.1.0/README_zh_CN.md)
| v1.0.0  |2024-04| Release |[v1.0.0](./manual/v1.0.0/README.MD)

</div>
