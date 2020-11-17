#include <Wire.h>
#include <menu.h>
#include <menuIO/liquidCrystalOut.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>

using namespace Menu;

  // LCD INSTANCE /////////////////////////////////////////
LiquidCrystal lcd(RS, EN, LCDPIN_4, LCDPIN_5, LCDPIN_6, LCDPIN_7);

  // ENCODER INSTANCE /////////////////////////////////////////
encoderIn<encA,encB> encoder;//simple quad encoder driver
encoderInStream<encA,encB> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};//negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);//1 is the number of keys

//input from the encoder + encoder button + serial
serialIn serial(Serial);
menuIn* inputsList[]={&encStream,&encButton,&serial};
chainStream<3> in(inputsList);//3 is the number of inputs

// Events Declaration /////////////////////////////////////////
result showEvent(eventMask e,navNode& nav,prompt& item) {
  Serial.print("event: ");
  Serial.println(e);
  return proceed;
}

// Cambiar Brillo /////////////////////////////////////////
result changebrightness(eventMask e,navNode& nav, prompt &item) {
  
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  Serial.println(BRIGHTNESS); 
  return proceed;
}

// Control Menu Lights /////////////////////////////////////
  
int redCtrl=LOW;
int yellowCtrl=LOW;
int greenCtrl=LOW;

result redlight(eventMask e,navNode& nav, prompt &item) {
  //Encender Luz ROJA
  control_spotlight(3, true );
  Serial.println("RED Light ON");
  return proceed;
}

result redlightOff(eventMask e,navNode& nav, prompt &item) {
  //Apagar luz ROJA
  control_spotlight(3, false );
  Serial.println("RED Light OFF");
  return proceed;
}

result yellowlight(eventMask e,navNode& nav, prompt &item) {
  //Encender Luz AMARILLA
  control_spotlight(2, true );
  Serial.println("YELLOW Light ON");
  return proceed;
}

result yellowlightOff(eventMask e,navNode& nav, prompt &item) {
  //Apagar luz AMARILLA
  control_spotlight(2, false );
  Serial.println("YELLOW Light OFF");
  return proceed;
}

result greenlight(eventMask e,navNode& nav, prompt &item) {
  //Encender Luz VERDE
  control_spotlight(1, true );
  Serial.println("GREEN Light ON");
  return proceed;
}

result greenlightOff(eventMask e,navNode& nav, prompt &item) {
  //Apagar luz VERDE
  control_spotlight(1, false );
  Serial.println("GREEN Light OFF");
  return proceed;
}

TOGGLE(redCtrl, setRedLight, "Red Light", doNothing,noEvent,noStyle
  ,VALUE(" On", HIGH,redlight, enterEvent )
  ,VALUE(" Off", LOW,redlightOff, enterEvent )
);

TOGGLE(yellowCtrl, setYellowLight, "Yellow Light", doNothing,noEvent,noStyle
  ,VALUE(" On", HIGH,yellowlight, enterEvent )
  ,VALUE(" Off", LOW,yellowlightOff, enterEvent )
);

TOGGLE(greenCtrl, setGreenLight, "Green Light", doNothing,noEvent,noStyle
  ,VALUE(" On", HIGH,greenlight, enterEvent )
  ,VALUE(" Off", LOW,greenlightOff, enterEvent )
);


  // Control Menu Lights /////////////////////////////////////
  
result speaker(eventMask e,navNode& nav, prompt &item) {
  //Encender speaker
  digitalWrite(SPEAKER, HIGH);
  Serial.println("Speaker ON");
  return proceed;
}

result speakerOff(eventMask e,navNode& nav, prompt &item) {
  //Apagar speaker
  digitalWrite(SPEAKER, LOW);
  Serial.println("Speaker OFF");
  return proceed;
}
int speakerCtrl=LOW;

TOGGLE(speakerCtrl, setSpeaker, "Speaker", doNothing,noEvent,noStyle
  ,VALUE(" On", HIGH,speaker, enterEvent )
  ,VALUE(" Off", LOW,speakerOff, enterEvent )
);

TOGGLE(speaker_on, setSpeakerOn,"Microphone: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",HIGH,doNothing,enterEvent)
  ,VALUE("Off",LOW,doNothing,enterEvent)
);

MENU(TestSpeaker,"Test speaker",showEvent,anyEvent,noStyle
  ,SUBMENU(setSpeaker) 
  ,EXIT("<Back")
);
MENU(TestLights,"Test lights",showEvent,anyEvent,noStyle
  ,SUBMENU(setRedLight)
  ,SUBMENU(setYellowLight)
  ,SUBMENU(setGreenLight)
  ,EXIT("<Back")
);

MENU(TestMicro,"Test microphone",showEvent,anyEvent,noStyle
  ,OP("Sub1",showEvent,anyEvent)
  ,OP("Sub2",showEvent,anyEvent)
  ,OP("Sub3",showEvent,anyEvent)
  ,EXIT("<Back")
);
MENU(Settings,"Settings",showEvent,anyEvent,noStyle
  ,FIELD(BRIGHTNESS,"Brillo LED","%",0,100,10,1,changebrightness,enterEvent,wrapStyle)
  ,FIELD(green_threshold,"Umbral verde","%",0,100,10,1,doNothing,enterEvent,wrapStyle)
  ,FIELD(yellow_threshold,"Umbral Amarillo","%",0,100,10,1,doNothing,enterEvent,wrapStyle)
  ,FIELD(red_threshold,"Umbral Rojo","%",0,100,10,1,doNothing,enterEvent,wrapStyle)
  ,SUBMENU(setSpeakerOn)
  ,EXIT("<Back")
);


MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle

  ,SUBMENU(Settings)
  ,SUBMENU(TestLights)
  ,SUBMENU(TestMicro)
  ,SUBMENU(TestSpeaker)

  ,EXIT("<Back")
);



#define MAX_DEPTH 2

MENU_OUTPUTS(out, MAX_DEPTH
  ,LIQUIDCRYSTAL_OUT(lcd,{0,0,20,4})
  ,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);//the navigation root object
