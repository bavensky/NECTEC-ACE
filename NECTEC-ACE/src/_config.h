#include <Arduino.h> 

/* BOARD INFO */
String DEVICE_NAME      = "KIDBRIGHT-CAR"; 

/* WIFI INFO */ 
String WIFI_SSID        = "cmmcWIFI";
String WIFI_PASSWORD    = "espertap";

/* MQTT INFO */ 
String MQTT_HOST        = "gb.netpie.io";
String MQTT_USERNAME    = "1JGmU67tQSxQTK6";
String MQTT_PASSWORD    = "NIURSS6xMbHjoFtWJKU+zYMBu5I=";
String MQTT_CLIENT_ID   = "qcvtDFMNts7xAi9n";
String MQTT_PREFIX      = "/nectecAce2018/gearname/";
int    MQTT_PORT        = 1883;
int PUBLISH_EVERY       = 1L * 1000;
int MQTT_CONNECT_TIMEOUT= 120; 

// mosquitto_sub -t "/nectecAce2018/gearname/#" -h gb.netpie.io -i qcvtDFMNts7xAi9n -u "1JGmU67tQSxQTK6" -P "NIURSS6xMbHjoFtWJKU+zYMBu5I=" -p 1883 -d