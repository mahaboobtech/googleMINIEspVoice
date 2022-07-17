#define WIFI_NAME "E"
#define WIFI_PASSWORD "bbkivines"
#define DEVICE_ID 1
#define DEVICE_NAME "GoogleAiProg"
#define TOKEN "Token add karo "


#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>

#define Relay_1 5
#define Relay_2 4
#define Relay_3 0


RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setRelayAc(boolean b) {remoteMe.getVariables()->setBoolean("relayAc", b); }
inline void setRelayfan(boolean b) {remoteMe.getVariables()->setBoolean("relayfan", b); }
inline void setRelaylight(boolean b) {remoteMe.getVariables()->setBoolean("relaylight", b); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************

void onRelayAcChange(boolean b) {
	Serial.printf("onRelayAcChange: b: %d\n",b);
  digitalWrite(Relay_3, b ? HIGH : LOW);
}
void onRelayfanChange(boolean b) {
	Serial.printf("onRelayfanChange: b: %d\n",b);
  digitalWrite(Relay_2, b ? HIGH : LOW);
}
void onRelaylightChange(boolean b) {
	Serial.printf("onRelaylightChange: b: %d\n",b);
  digitalWrite(Relay_1, b ? HIGH : LOW);
}




void setup() {
	Serial.begin(9600);

	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
  pinMode(Relay_3, OUTPUT);

  digitalWrite(Relay_1, LOW);
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);

	remoteMe.getVariables()->observeBoolean("relayAc" ,onRelayAcChange);
	remoteMe.getVariables()->observeBoolean("relayfan" ,onRelayfanChange);
	remoteMe.getVariables()->observeBoolean("relaylight" ,onRelaylightChange);

	remoteMe.setConnector(new RemoteMeSocketConnector());
	remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);
}


void loop() {
	remoteMe.loop();
}
