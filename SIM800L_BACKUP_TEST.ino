#include "GSM_MQTT.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <avr/pgmspace.h>
MPU6050 accelgyro;
#define ACCINTPIN 0
volatile bool accInterrupt = false;
boolean interruptA = false;
int numberOfReadings = 4; //0 included
int numberOfPackets = 60; //0 included
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned int PacketID;
//const PROGMEM char MQTT_HOST[] = {"159.65.194.72"};
String MQTT_HOST = "159.65.194.72";
/*
   MQTT host address
*/
int ledPin = 13;
String MQTT_PORT = "1883";
const PROGMEM char MQTT_ID[] = {'02S'};
const PROGMEM char MQTT_USERNAME[] = {'3'};
const PROGMEM char MQTT_PASSWORD[] = {'214466399fa074985b98f99d6bf48945'};
/*
   MQTT port
*/
//SoftwareSerial mySerial(10, 11); // RX, TX
/*
   Software Serial through which mqtt events log is printed at 9600 baud rate
*/
void GSM_MQTT::AutoConnect(void)
{
  /*
     Use this function if you want to use autoconnect(and auto reconnect) facility
     This function is called whenever TCP connection is established (or re-established).
     put your connect codes here.
  */
  connect("02w", 1, 1, "3", "214466399fa074985b98f99d6bf48945", 1, 0, 0, 0, "", "");
  /*    void connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char *UserName, char *Password, char CleanSession, char WillFlag, char WillQoS, char WillRetain, char *WillTopic, char *WillMessage);
          ClientIdentifier  :Is a string that uniquely identifies the client to the server.
                            :It must be unique across all clients connecting to a single server.(So it will be better for you to change that).
                            :It's length must be greater than 0 and less than 24
                            :Example "qwerty"
          UserNameFlag      :Indicates whether UserName is present
                            :Possible values (0,1)
                            :Default value 0 (Disabled)
          PasswordFlag      :Valid only when  UserNameFlag is 1, otherwise its value is disregarded.
                            :Indicates whether Password is present
                            :Possible values (0,1)
                            :Default value 0 (Disabled)
          UserName          :Mandatory when UserNameFlag is 1, otherwise its value is disregarded.
                            :The UserName corresponding to the user who is connecting, which can be used for authentication.
          Password          :alid only when  UserNameFlag and PasswordFlag are 1 , otherwise its value is disregarded.
                            :The password corresponding to the user who is connecting, which can be used for authentication.
          CleanSession      :If not set (0), then the server must store the subscriptions of the client after it disconnects.
                            :If set (1), then the server must discard any previously maintained information about the client and treat the connection as "clean".
                            :Possible values (0,1)
                            :Default value 1
          WillFlag          :This flag determines whether a WillMessage published on behalf of the client when client is disconnected involuntarily.
                            :If the WillFlag is set, the WillQoS, WillRetain, WillTopic, WilMessage fields are valid.
                            :Possible values (0,1)
                            :Default value 0 (Disables will Message)
          WillQoS           :Valid only when  WillFlag is 1, otherwise its value is disregarded.
                            :Determines the QoS level of WillMessage
                            :Possible values (0,1,2)
                            :Default value 0 (QoS 0)
          WillRetain        :Valid only when  WillFlag is 1, otherwise its value is disregarded.
                            :Determines whether the server should retain the Will message.
                            :Possible values (0,1)
                            :Default value 0
          WillTopic         :Mandatory when  WillFlag is 1, otherwise its value is disregarded.
                            :The Will Message will published to this topic (WillTopic) in case of involuntary client disconnection.
          WillMessage       :Mandatory when  WillFlag is 1, otherwise its value is disregarded.
                            :This message (WillMessage) will published to WillTopic in case of involuntary client disconnection.
  */
  
}
void GSM_MQTT::OnConnect(void)
{
  subscribe(0, _generateMessageID(), "3/test", 1);
  /*
     This function is called when mqqt connection is established.
     put your subscription publish codes here.
  */
  //  subscribe(0, _generateMessageID(), "SampleTopic", 1);
  /*    void subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS);
          DUP       :This flag is set when the client or server attempts to re-deliver a SUBSCRIBE message
                    :This applies to messages where the value of QoS is greater than zero (0)
                    :Possible values (0,1)
                    :Default value 0
          Message ID:The Message Identifier (Message ID) field
                    :Used only in messages where the QoS levels greater than 0 (SUBSCRIBE message is at QoS =1)
          SubTopic  :Topic names to which  subscription is needed
          SubQoS    :QoS level at which the client wants to receive messages
                    :Possible values (0,1,2)
                    :Default value 0
  */

  publish(0, 0, 0, _generateMessageID(), "3/s", "c1");
  /*  void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message);
      DUP       :This flag is set when the client or server attempts to re-deliver a PUBLISH message
                :This applies to messages where the value of QoS is greater than zero (0)
                :Possible values (0,1)
                :Default value 0
      QoS       :Quality of Service
                :This flag indicates the level of assurance for delivery of a PUBLISH message
                :Possible values (0,1,2)
                :Default value 0
      RETAIN    :if the Retain flag is set (1), the server should hold on to the message after it has been delivered to the current subscribers.
                :When a new subscription is established on a topic, the last retained message on that topic is sent to the subscriber
                :Possible values (0,1)
                :Default value 0
      Message ID:The Message Identifier (Message ID) field
                :Used only in messages where the QoS levels greater than 0
      Topic     :Publishing topic
      Message   :Publishing Message
  */
}
void GSM_MQTT::OnMessage(char *Topic, int TopicLength, char *Message, int MessageLength)
{
   publish(0, 0, 0, _generateMessageID(), "3/q", ":)");
  /*
    This function is called whenever a message received from subscribed topics
    put your subscription publish codes here.
  */

  /*
     Topic        :Name of the topic from which message is coming
     TopicLength  :Number of characters in topic name
     Message      :The containing array
     MessageLength:Number of characters in message
  */
  //mySerial.println(TopicLength);
 // mySerial.println(Topic);
  //mySerial.println(MessageLength);
  //mySerial.println(Message);

}
GSM_MQTT MQTT(20);
/*
   20 is the keepalive duration in seconds
*/

void setup()
{
  pinMode(ledPin, OUTPUT);
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif   
    accelerometerSetup();
  // initialize mqtt:
  // GSM modem should be connected to Harware Serial
  //  index =0;
  MQTT.begin();

  /*
     You can write your code here
  */

}
void loop()
{

  /*
     You can write your code here
  */
   if (MQTT.available())
         {
          digitalWrite(ledPin, LOW);
    if(interruptA){
      interruptA = false;
         //Do something when the threshold is triggered.
       
           sendPublishPackets();
                               // wait for a second 
          }  
         
       }else{
               digitalWrite(ledPin, HIGH);
             }

  MQTT.processing();
}
void wakeUpMotion() {
  if (interruptA == 0) {
    interruptA = true;
  }
}
void accelerometerSetup() {

  pinMode(ACCINTPIN, INPUT_PULLUP);

  // initialize device
  //Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // use the code below to change accel/gyro offset values

  //Serial.println("Updating internal sensor offsets...");
  // -76	-2359	1688	0	0	0
  /*Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
  Serial.print("\n");
  /*accelgyro.setXGyroOffset(170);
  accelgyro.setYGyroOffset(-22);
  accelgyro.setZGyroOffset(13952);
  accelgyro.setXAccelOffset(0);
  accelgyro.setYAccelOffset(0);
  accelgyro.setZAccelOffset(0);
  Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
  Serial.print("\n");*/


  // verify connection
  //Serial.println("Testing device connections...");
  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  // config low power

  accelgyro.setIntMotionEnabled(1);//Set Motion Detection interrupt enabled status.
  accelgyro.setIntFreefallEnabled(0);
  accelgyro.setIntZeroMotionEnabled(0);
  accelgyro.setIntFIFOBufferOverflowEnabled(0);
  accelgyro.setIntDataReadyEnabled(0); //New interrupt enabled status
  accelgyro.setDHPFMode(3); //New high-pass filter configuration more than 1.25Hz pass
  accelgyro.setDLPFMode(5); //New low-pass filter configuration below 10Hz pass
  
  //accelgyro.setFullScaleGyroRange(0); //0 = +/- 250 degrees/sec | 1 = +/- 500 degrees/sec | 2 = +/- 1000 degrees/sec | 3 =  +/- 2000 degrees/sec
  accelgyro.setFullScaleAccelRange(0); //0 = +/- 2g | 1 = +/- 4g | 2 = +/- 8g | 3 =  +/- 16g 
  accelgyro.setMotionDetectionThreshold(1);  //20 - 2
  accelgyro.setMotionDetectionDuration(1); //New motion detection duration threshold value (LSB = 1ms)
  
  accelgyro.setInterruptMode(1); //New interrupt mode (0=active-high, 1=active-low)
  accelgyro.setInterruptDrive(0); //New interrupt drive mode (0=push-pull, 1=open-drain)
  accelgyro.setInterruptLatch(0); //New latch mode (0=50us-pulse, 1=latch-until-int-cleared)
  accelgyro.setInterruptLatchClear(0); //New latch clear mode (0=status-read-only, 1=any-register-read)
  accelgyro.setRate(7); //Set the rate to disable the gyroscope
  accelgyro.setWakeFrequency(3); //Wake up the accelerometer at 1.25Hz to save power
  accelgyro.setWakeCycleEnabled(1); //Enable only accel. ON - Low power mode, waking it up from time to time

  delay(50);
  accelgyro.setTempSensorEnabled(0);
  accelgyro.setStandbyXGyroEnabled(1);
  accelgyro.setStandbyYGyroEnabled(1);
  accelgyro.setStandbyZGyroEnabled(1);
  delay(50);

  attachInterrupt(ACCINTPIN, wakeUpMotion, RISING);
}
char* returnRecording() {
  char myConcatenation[80];
  String sensorBuffer = "";
  for (int i=0; i <= numberOfReadings; i++){
    accelgyro.getAcceleration(&ax, &ay, &az);
    sprintf(myConcatenation,"%d\t%d\t%d\t%d",ax,ay,az, millis()); /// SKAL IKKE VÆRE INT! men unsigned long
    sensorBuffer.concat(myConcatenation);
    sensorBuffer.concat("\n");
    //accelgyro.getAcceleration(&ax, &ay, &az);
    delay(20);
   }
   //sensorCharBuffer= sensorBuffer;
   char sensorCharBuffer[sensorBuffer.length()];
   sensorBuffer.toCharArray(sensorCharBuffer, sensorBuffer.length());
 return sensorCharBuffer;
}
void sendPublishPackets(){
  PacketID = MQTT._generateMessageID();
           for (int i=0; i <= numberOfPackets; i++){
              MQTT.publish(0, 0, 0, PacketID, "3/s", returnRecording());
              delay(10);
          
            }
          //delay(1000);  
}
