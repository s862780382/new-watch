#define SSID        "*****" //改为你的Wi-Fi名称

#define PASSWORD    "*****"//Wi-Fi密码

#define HOST_NAME   "api.heclouds.com"

#define DEVICEID    "******" //OneNet上的设备ID

#define PROJECTID   "******" //OneNet上的产品ID

#define HOST_PORT   (80)

String apiKey="*****************";//与你的设备绑定的APIKey



#define INTERVAL_SENSOR   2000             //定义传感器采样时间间隔  597000 

#define INTERVAL_NET      300000            //定义发送时间 

//传感器部分================================   
#include <Wire.h>                                  //调用库  

#include <ESP8266.h>

#include <I2Cdev.h>                                //调用库

#define INTERVAL_SENSOR   2000             //定义传感器采样时间间隔  597000 

#define INTERVAL_NET      300000            //定义发送时间 
  

/*******温湿度*******/

#include <Microduino_SHT2x.h>

//WEBSITE     

char buf[10];



#define INTERVAL_sensor 2000

unsigned long sensorlastTime = millis();



float tempOLED, humiOLED;



#define INTERVAL_OLED 1000



String mCottenData;

String jsonToSend;



//传感器值的设置 

float sensor_tem, sensor_hum, sensor_lux;                    //传感器温度、湿度

char  sensor_tem_c[7], sensor_hum_c[7];    //换成char数组传输

#include <SoftwareSerial.h>

#define EspSerial mySerial

#define UARTSPEED  9600

SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */

ESP8266 wifi(&EspSerial);

//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象

unsigned long net_time1 = millis();                          //数据上传服务器时间

unsigned long sensor_time = millis();                        //传感器采样时间计时器



//int SensorData;                                   //用于存储传感器数据

String postString;                                //用于存储发送数据的字符串

//String jsonToSend;                                //用于存储发送的json格式参数


//OLED屏幕显示设置

#include <U8glib.h>//使用OLED需要包含这个头文件

#define INTERVAL_LCD 20 //定义OLED刷新时间间隔 

unsigned long lcd_time = millis(); //OLED刷新时间计时器

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //设置OLED型号 

//-------字体设置，大、中、小

#define setFont_L u8g.setFont(u8g_font_7x13)

#define setFont_M u8g.setFont(u8g_font_fixed_v0r)

#define setFont_S u8g.setFont(u8g_font_fixed_v0r)

#define setFont_SS u8g.setFont(u8g_font_fub25n)


//汉字取模

static unsigned char u8g_you_bits[] U8G_PROGMEM =
{
/*--  文字:  邮  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x10,0x00,0x10,0x0E,0x10,0x0A,0xFE,0x0A,0x92,0x06,0x92,0x06,0xFE,0x0A,0x92,0x0A,
0x92,0x0A,0x92,0x06,0xFE,0x02,0x82,0x02,0x00,0x00,
};

static unsigned char u8g_bei_bits[] U8G_PROGMEM ={
/*--  文字:  北  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x90,0x00,0x90,0x00,0x90,0x08,0x90,0x04,0x9E,0x02,0x90,0x01,0x90,0x00,0x90,0x00,
0x98,0x00,0x96,0x08,0x90,0x08,0x10,0x0F,0x00,0x00,
};

//“一”
/*--  文字:  一  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
static unsigned char u8g_yi_bits[] U8G_PROGMEM =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x0F,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

//“二”
static unsigned char u8g_er_bits[] U8G_PROGMEM =
{
  /*--  文字:  二  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x00,0x00,0x00,0xFC,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFE,0x0F,0x00,0x00,0x00,0x00,
};

//“三”
static unsigned char u8g_san_bits[] U8G_PROGMEM =
{
  /*--  文字:  三  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x00,0xFC,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x0F,0x00,0x00,
};

//“四”
static unsigned char u8g_si_bits[] U8G_PROGMEM =
{
  /*--  文字:  四  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x00,0xFC,0x0F,0x24,0x09,0x24,0x09,0x24,0x09,0x24,0x09,0x24,0x09,0x14,0x0E,
0x0C,0x08,0x04,0x08,0xFC,0x0F,0x04,0x08,0x00,0x00,
};

//“五”
static unsigned char u8g_wu_bits[] U8G_PROGMEM =
{
  /*--  文字:  五  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x00,0xFE,0x07,0x20,0x00,0x20,0x00,0x20,0x00,0xFC,0x03,0x10,0x02,0x10,0x02,
0x10,0x02,0x08,0x02,0x08,0x02,0xFE,0x0F,0x00,0x00,
};

//“六”
static unsigned char u8g_liu_bits[] U8G_PROGMEM =
{
  /*--  文字:  六  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x20,0x00,0x40,0x00,0x40,0x00,0x00,0x00,0xFE,0x0F,0x00,0x00,0x10,0x01,0x10,0x02,
0x08,0x04,0x08,0x04,0x04,0x08,0x02,0x08,0x00,0x00,
};

//“日”
static unsigned char u8g_ri_bits[] U8G_PROGMEM =
{
  /*--  文字:  日  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x00,0xFC,0x07,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x07,0x04,0x04,0x04,0x04,
0x04,0x04,0x04,0x04,0xFC,0x07,0x04,0x04,0x00,0x00,
};


//“星”
static unsigned char u8g_xing_bits[] U8G_PROGMEM =
{
  /*--  文字:  星  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0xFC,0x07,0x04,0x04,0xFC,0x07,0x04,0x04,0xFC,0x07,0x40,0x00,0x44,0x00,0xFC,0x07,
0x42,0x00,0xF8,0x03,0x40,0x00,0xFE,0x0F,0x00,0x00,
};

//“期”
static unsigned char u8g_qi_bits[] U8G_PROGMEM =
{
/*--  文字:  期  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x24,0x00,0x24,0x0F,0x7E,0x09,0x24,0x09,0x3C,0x0F,0x24,0x09,0x3C,0x09,0x24,0x0F,
0x7E,0x09,0x00,0x09,0x24,0x09,0xC2,0x0C,0x00,0x00,
};

//“时”
static unsigned char u8g_shi_bits[] U8G_PROGMEM =
{
  /*--  文字:  时  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x00,0x04,0x1E,0x04,0x12,0x04,0xD2,0x0F,0x12,0x04,0x1E,0x04,0x92,0x04,0x12,0x05,
0x12,0x05,0x1E,0x04,0x12,0x04,0x00,0x07,0x00,0x00,
};

//“间”
static unsigned char u8g_jian_bits[] U8G_PROGMEM =
{
/*--  文字:  间  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0xE4,0x0F,0x08,0x08,0x00,0x08,0xF4,0x0B,0x14,0x0A,0x14,0x0A,0xF4,0x0B,0x14,0x0A,
0x14,0x0A,0xF4,0x0B,0x04,0x08,0x04,0x0E,0x00,0x00,
};

//“温”
static unsigned char u8g_wen_bits[] U8G_PROGMEM =
{
  /*--  文字:  温  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0xE0,0x03,0x22,0x02,0xE4,0x03,0x20,0x02,0xE0,0x03,0x02,0x00,0xF4,0x07,0x50,0x05,
0x58,0x05,0x54,0x05,0x52,0x05,0xF8,0x0F,0x00,0x00,
};

//“度”
static unsigned char u8g_du_bits[] U8G_PROGMEM =
{
/*--  文字:  度  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x80,0x00,0xFC,0x0F,0x24,0x02,0xFC,0x0F,0x24,0x02,0xE4,0x03,0x04,0x00,0xF4,0x07,
0x24,0x04,0x44,0x02,0x84,0x01,0x72,0x0E,0x00,0x00,
};

static unsigned char u8g_shi1_bits[] U8G_PROGMEM =
{
/*--  文字:  湿  --*/
/*--  新宋体10;  此字体下对应的点阵为：宽x高=14x13   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x13  --*/
0x02,0x00,0xF4,0x07,0x10,0x04,0xF0,0x07,0x12,0x04,0xF4,0x07,0x40,0x01,0x48,0x09,
0x50,0x05,0x44,0x01,0x42,0x01,0xF8,0x0F,0x00,0x00,
};

Tem_Hum_S2 TempMonitor;

//时钟设置
#include <Microduino_RTC.h>
#include <TimeLib.h>
unsigned long timer_draw,timer;
String dateStr, ret;

//如果开启下面#define set_time的标志，则按照rtcTime中的时间设置RTC模块中的时间
//#define set_time//设置完下面时间上传结束后将此行注释掉即可按照上次断电后的时间继续读秒

DateTime rtcTime = {2018,12,0,23, 11, 00, 10};//时间格式（年，月,星期，日，时，分，秒）初始时间

RTC rtc;
time_t prevDisplay = 0;

//闹钟设置
#define buzzer_pin 6    //定义蜂鸣器引脚D6
#define mic_pin A0     //麦克风引脚A0
void setup(void)     //初始化函数  

{       

  //初始化串口波特率  

    Wire.begin();

    Serial.begin(115200);

    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    Serial.print(F("setup begin\r\n"));

    delay(100);

//    pinMode(sensorPin_1, INPUT);



  WifiInit(EspSerial, UARTSPEED);



  Serial.print(F("FW Version:"));

  Serial.println(wifi.getVersion().c_str());



  if (wifi.setOprToStationSoftAP()) {

    Serial.print(F("to station + softap ok\r\n"));

  } else {

    Serial.print(F("to station + softap err\r\n"));

  }



  if (wifi.joinAP(SSID, PASSWORD)) {

    Serial.print(F("Join AP success\r\n"));



    Serial.print(F("IP:"));

    Serial.println( wifi.getLocalIP().c_str());

  } else {

    Serial.print(F("Join AP failure\r\n"));

  }



  if (wifi.disableMUX()) {

    Serial.print(F("single ok\r\n"));

  } else {

    Serial.print(F("single err\r\n"));

  }



  Serial.print(F("setup end\r\n"));

    

  



rtc.begin();
  //如果之前开启了#define set_time的标志，则按照rtcTime中的时间设置RTC模块中的时间
#ifdef set_time
  rtc.clearAll();
  rtc.setDateTime(rtcTime);
#endif
  rtc.getDateTime(&rtcTime);//获取RTC时间
  setTime(rtcTime.hour, rtcTime.minute, rtcTime.second, rtcTime.day, rtcTime.month, rtcTime.year);//使用RTC时间校准本地时间



  pinMode(buzzer_pin, OUTPUT);

  pinMode(mic_pin, INPUT);

}

void loop(void)     //循环函数  

{   

  if (sensor_time > millis())  sensor_time = millis();  


  if(millis() - sensor_time > INTERVAL_SENSOR)              //传感器采样时间间隔  

  {  

    getSensorData();                                        //读串口中的传感器数据

    sensor_time = millis();

  }  



    

  if (net_time1 > millis())  net_time1 = millis();

  

  if (millis() - net_time1 > INTERVAL_NET)                  //发送数据时间间隔

  {                

    updateSensorData();                                     //将数据上传到服务器的函数

    net_time1 = millis();

  }

 u8g.firstPage();

 do {

 setFont_L;
//打印北邮
//u8g.drawXBMP( 111, 21, 16, 13, u8g_you_bits);
//u8g.drawXBMP( 99, 21, 16, 13, u8g_bei_bits);

//显示温度
u8g.drawXBMP( 0,33, 16, 13, u8g_wen_bits);
u8g.drawXBMP( 12,33 , 16, 13, u8g_du_bits);
u8g.setPrintPos(25,45);
u8g.print(":");
u8g.setPrintPos(40, 45);
u8g.print(sensor_tem);
u8g.drawCircle(84,38,2) ;
u8g.setPrintPos(89, 45);
u8g.print("C");
 
//显示光强
 //u8g.setPrintPos(0, 30);

 //u8g.print(sensor_lux);

 //u8g.setPrintPos(40, 30);

 //u8g.print("lux");

//显示湿度
u8g.drawXBMP( 0,48, 16, 13, u8g_shi1_bits);
u8g.drawXBMP( 12,48, 16, 13, u8g_du_bits);
u8g.setPrintPos(25,60);
u8g.print(":");
u8g.setPrintPos(40,60);
u8g.print(sensor_hum);
u8g.setPrintPos(76,60);
u8g.print("%");

//显示时间
serialClockDisplay(year(), month(), day(), hour(), minute(), second());


//打印笑脸
u8g.drawCircle(112,50,13);
u8g.drawCircle(107,48, 3, U8G_DRAW_UPPER_LEFT); 
u8g.drawCircle(107,48, 3, U8G_DRAW_UPPER_RIGHT); 
u8g.drawCircle(117,48, 3, U8G_DRAW_UPPER_LEFT); 
u8g.drawCircle(117,48, 3, U8G_DRAW_UPPER_RIGHT);
u8g.drawCircle(112,53, 4, U8G_DRAW_LOWER_LEFT); 
u8g.drawCircle(112,53, 4, U8G_DRAW_LOWER_RIGHT);
 }while( u8g.nextPage() ); 

//闹钟设置以及时间长度

alarm_work();
//仿照此例可设置多个闹钟
}



void getSensorData(){  

    sensor_tem = TempMonitor.getTemperature();  

    sensor_hum = TempMonitor.getHumidity();   

    dtostrf(sensor_tem, 2, 1, sensor_tem_c);

    dtostrf(sensor_hum, 2, 1, sensor_hum_c);

}

void updateSensorData() {

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据

    Serial.print("create tcp ok\r\n");



jsonToSend="{\"Temperature\":";

    dtostrf(sensor_tem,1,2,buf);

    jsonToSend+="\""+String(buf)+"\"";

    jsonToSend+=",\"Humidity\":";

    dtostrf(sensor_hum,1,2,buf);

    jsonToSend+="\""+String(buf)+"\"";
    
    jsonToSend+="}";







    postString="POST /devices/";

    postString+=DEVICEID;

    postString+="/datapoints?type=3 HTTP/1.1";

    postString+="\r\n";

    postString+="api-key:";

    postString+=apiKey;

    postString+="\r\n";

    postString+="Host:api.heclouds.com\r\n";

    postString+="Connection:close\r\n";

    postString+="Content-Length:";

    postString+=jsonToSend.length();

    postString+="\r\n";

    postString+="\r\n";

    postString+=jsonToSend;

    postString+="\r\n";

    postString+="\r\n";

    postString+="\r\n";



  const char *postArray = postString.c_str();                 //将str转化为char数组

  Serial.println(postArray);

  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)

  Serial.println("send success");   

     if (wifi.releaseTCP()) {                                 //释放TCP连接

        Serial.print("release tcp ok\r\n");

        } 

     else {

        Serial.print("release tcp err\r\n");

        }

      postArray = NULL;                                       //清空数组，等待下次传输数据

  

  } else {

    Serial.print("create tcp err\r\n");

  }

}


//OLED屏幕日期打印函数
void serialClockDisplay(int _year, int _month, int _day, int _hour, int _minute, int _second) {
 setFont_L;
   //打印日期
  u8g.setPrintPos(0,15);
 u8g.print(_year);
 u8g.setPrintPos(30, 15);
 u8g.print("/");
 u8g.setPrintPos(40,15);
 u8g.print(_month);
 u8g.setPrintPos(55,15);
 u8g.print("/");
 u8g.setPrintPos(65, 15);
 u8g.print(_day);


//打印星期几
u8g.drawXBMP( 85, 5, 16, 13, u8g_xing_bits);
u8g.drawXBMP( 98, 5, 16, 13, u8g_qi_bits);
int x = 0, sum = 0, m,week=0;
  week = (_year - 2018) * 365;
  for (int i = 2018; i < _year; i++)
  {
    if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
    {
      x = x + 1;
    }
  }
  week = week + x;
  (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0)) ? m = 29 : m = 28;    //判断闰年
  switch (_month) //case 不加 break; 时顺序执行，所以这里顺序不能变。
  {
  case 12:
    sum += 30;
  case 11:
    sum += 31;
  case 10:
    sum += 30;
  case 9:
    sum += 31;
  case 8:
    sum += 31;
  case 7:
    sum += 30;
  case 6:
    sum += 31;
  case 5:
    sum += 30;
  case 4:
    sum += 31;
  case 3:
    sum += m;
  case 2:
    sum += 31;
  case 1:
    sum += _day;
    break;
  default:
    break;
  }
  week = week + sum;
  switch (week % 7)
  {
  case 0:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_ri_bits);
    break;
  case 1:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_yi_bits);
    break;
  case 2:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_er_bits);
    break;
  case 3:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_san_bits);
    break;
  case 4:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_si_bits);
    break;
  case 5:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_wu_bits);
    break;
  case 6:
    u8g.drawXBMP( 110, 5, 16, 13, u8g_liu_bits);
    break;
  default:
    break;
  }

 //打印时间
 u8g.drawXBMP( 0, 18, 16, 13, u8g_shi_bits);
 u8g.drawXBMP( 12, 18, 16, 13, u8g_jian_bits);
 u8g.setPrintPos(25,30);
 u8g.print(":");
 //如果小时数为一位数，在前面添0
 if(_hour>=10)
 {
 u8g.setPrintPos(40, 30);
 u8g.print(_hour);
 }
 else
 {
  u8g.setPrintPos(40, 30);
  u8g.print("0");
  u8g.setPrintPos(47, 30);
  u8g.print(_hour);
 }

 //闪烁
 if(_second%2==0)
 {
 u8g.setPrintPos(55, 30);
 u8g.print(":");
 }
 else
 {
 u8g.setPrintPos(55, 30);
 u8g.print(" ");
 }
 
 //如果分钟数为一位数，在前面添0
 if(_minute>=10)
 {
 u8g.setPrintPos(65,30);
 u8g.print(_minute);
 }
 else
 {
  u8g.setPrintPos(65,30);
  u8g.print("0");
  u8g.setPrintPos(72,30);
  u8g.print(_minute);
 }




 //如果秒数为一位数，在前面添加0
 if(_second>=10)
 {
  setFont_M;
  u8g.setPrintPos(85, 30);
  u8g.print(_second);
 }
 else
 {
  setFont_M;
  u8g.setPrintPos(85, 30);
  u8g.print("0");
  u8g.setPrintPos(92, 30);
  u8g.print(_second);
 }
 }
 //闹钟歌曲设置
 bool sense;

 void alarm_work()
{
    //这里设置了八点的闹钟，持续五分钟
    if(hour()==8&&minute()>=0&&minute()<=4) {
      if(analogRead(mic_pin)>400) {
      sense=true;
    }
    if(sense) {
      noTone(buzzer_pin);
    } else {
       tone(buzzer_pin,400);
       delay(1000);
      //在端口输出频率
    }
  } else {
    sense=false;
    noTone(buzzer_pin);
  }
}
