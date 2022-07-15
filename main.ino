#define WIFI_NAME "bs"
#define WIFI_PASSWORD "bbkivines"
#define DEVICE_ID 1
#define DEVICE_NAME "GoogleAiProg"
#define TOKEN ""


#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>

#define Relay_1 D1
#define Relay_2 D2
#define Relay_3 D3



RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setRelay_1(boolean b) {remoteMe.getVariables()->setBoolean("relay_1", b); }
inline void setRelay_2(boolean b) {remoteMe.getVariables()->setBoolean("relay_2", b); }
inline void setRelay_3(boolean b) {remoteMe.getVariables()->setBoolean("relay_3", b); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************

void onRelay_1Change(boolean b) {
	Serial.printf("onRelay_1Change: b: %d\n",b);
  digitalWrite(Relay_1, b ? HIGH : LOW);
}
void onRelay_2Change(boolean b) {
	Serial.printf("onRelay_2Change: b: %d\n",b);
  digitalWrite(Relay_1, b ? HIGH : LOW);
}
void onRelay_3Change(boolean b) {
	Serial.printf("onRelay_3Change: b: %d\n",b);
  digitalWrite(Relay_1, b ? HIGH : LOW);
}




void setup() {
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
  pinMode(Relay_3, OUTPUT);

  digitalWrite(Relay_1, LOW);
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);

	Serial.begin(115200);

	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

	remoteMe.getVariables()->observeBoolean("relay_1" ,onRelay_1Change);
	remoteMe.getVariables()->observeBoolean("relay_2" ,onRelay_2Change);
	remoteMe.getVariables()->observeBoolean("relay_3" ,onRelay_3Change);

	remoteMe.setConnector(new RemoteMeSocketConnector());
	remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);
}


void loop() {
	remoteMe.loop();
}
