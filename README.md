# xihe-iot-gateway

<div style="font-size:18px;">
Industrial Edge IoT Gateway

[English](./README.md) [中文简体](./README_zh_CN.md) [中文繁體](./README_zh_TW.md) 

</div>

>### <h1>Catalog</h1>

[<b style="font-size:24px;">1.Introduction</b>](#<h1>1.Introduction</h1>)    
[<b style="font-size:24px;">2.UpdateNotes</b>](#<h1>2.UpdateNotes</h1>)   

>### <h1>1.Introduction</h1>

<center><h1><b>Fateit-Xihe Industrial Edge IoT gateway</b></h1></center><br>

<h3 style="color:red;letter-spacing: 1px;">*See the <b>user manual</b> for more details,the appendix contains usage examples based on Raspi 4b.</h3><br> 

![avatar](images/main-en_US.png)
<div style="font-size:16px;">

&nbsp;&nbsp;&nbsp;&nbsp;Fateit-Xihe is a free industrial Edge IoT gateway that can run across platforms, with rich functions, stable and reliable operation and easy to use. It supports different types of devices (PLC, semiconductor,iot devices), pushes changing data through MQTT, and provides http-based lightweight data read and write interface.<br>
&nbsp;&nbsp;&nbsp;&nbsp;Lower the threshold of equipment interconnection, get through the difficulties of <b> equipment interaction </b>, <b> data collection </b>, <b> data landing </b>, so as to help small, medium and micro enterprises to realize the transformation of digital and intelligent upgrading.<br> For the enterprise to improve the production, quality and efficiency, so as to improve the overall competitiveness of the enterprise.<br>\
<b>Main functions:</b><br>
1. Built-in MQTT v3 Broker: native <b>high-performance</b> Mqtt server, supports: tcp(1883), websocket(8083), no need to deploy another MQTT Broker. <br>
2. Supported drivers: <b>Modbus(tcp)</b>, <b>Semiconductor protocol: SECS/GEM(hsms)</b>, <b>OPC UA</b>, <b>Iot Message (mqtt)</b>, and will be expanded as planned in the future. <br>
3. Data is pushed to MQTT based on event changes. <br>
4. After disconnection and reconnection, the device starts to connect automatically. <br>
5. Unique memory <b>data structure</b> design, with stronger multi-point reading performance. <br>
6. <b>One-click startup</b>, simple online configuration, ready to use out of the box, low operation and maintenance costs, and no need for cumbersome configuration. <br>
7. <b>Support message Cassandra, Kafka push, convenient for big data storage, transmission and analysis [Enabling will increase additional resource overhead]</b><br>
8. <b>Fateit is supported by a vibrant digital ecosystem</b><br>
9. suitable for running in the <b>edge end</b>, but also suitable for running in <b>the server</b>, to meet the user of a variety of actual scenarios.<br>
&nbsp;&nbsp;&nbsp;&nbsp;Hide the complexity of device protocol docking, facilitate the rapid implementation of device docking, provide simplified, unified, generalized, and advanced data docking methods and data structures, allowing users to focus more on the upper-layer architecture, Focus on its own core business and accelerate the development of the enterprise. <br><br><br>

</div>



>### <h1>2.UpdateNotes</h1>


<center><h1><b>2.Update Notes</b></h1></center><br>

<h3 style="color:red;letter-spacing: 1px;">*更多详细信息请查看<b>用户手册</b>，附录有基于Raspi 4b的应用实例。</h3><br>
<div style="font-size:16px;">

|Version|Date|Notes|Details
|-|-|-|-
| V1.1.0  |2024-07| <b> 1. Add support of Mqtt protocol for label read and write, and system event push <br> 2. Add open access timestamp interface: timestamp </b>|[v1.1.0](./manual/v1.1.0/README.md)
| v1.0.0  |2024-04| Release |[v1.0.0](./manual/v1.0.0/README.md)


</div>
