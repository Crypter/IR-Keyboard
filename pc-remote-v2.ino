//#define DECODE_NEC
//#define DECODE_RC5
//#define DECODE_RC6
#define NO_LEGACY_COMPATIBILITY
#define IR_RECEIVE_PIN 5

#include <IRremote.h>



#include "HID-Project.h"


void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(IR_RECEIVE_PIN, INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);

  Mouse.begin();
  Keyboard.begin();
  Consumer.begin();
  System.begin();
  Serial.begin(115200);
}

void loop() {
  if (IrReceiver.decode()) {


    //uint32_t rawData = IrReceiver.decodedIRData.decodedRawData;
    uint64_t data = 0;
    memcpy(&data, &IrReceiver.decodedIRData, sizeof(IrReceiver.decodedIRData.protocol) + sizeof(IrReceiver.decodedIRData.address) + sizeof(IrReceiver.decodedIRData.command));
    uint32_t low = data;
    uint32_t high = (data >> 32);
    char buf[64];
    sprintf(buf, "0x%08lX%08lX", high, low);
    Serial.println(buf);
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    if (data == 0x000000100000000E) Consumer.write(MEDIA_VOLUME_UP);
    else if (data == 0x000000110000000E) Consumer.write(MEDIA_VOLUME_DOWN);
    else if (data == 0x0000000D0000000E) Consumer.write(MEDIA_VOLUME_MUTE);
    else if (data == 0x000000320000000E) Consumer.write(MEDIA_PLAY_PAUSE);
    else if (data == 0x0000003E0000000E) Consumer.write(CONSUMER_BROWSER_HOME);

    else if (data == 0x000000260000000E) Keyboard.write(HID_KEYBOARD_ESCAPE);
    else if (data == 0x000000200000000E) Keyboard.write(HID_KEYBOARD_PAGE_UP);
    else if (data == 0x000000210000000E) Keyboard.write(HID_KEYBOARD_PAGE_DOWN);
    
    else if (data == 0x000000060000000E) Keyboard.write(HID_KEYBOARD_RIGHTARROW);
    else if (data == 0x000000020000000E) Keyboard.write(HID_KEYBOARD_UPARROW);
    else if (data == 0x000000040000000E) Keyboard.write(HID_KEYBOARD_LEFTARROW);
    else if (data == 0x000000080000000E) Keyboard.write(HID_KEYBOARD_DOWNARROW);
    else if (data == 0x000000050000000E) Keyboard.write(HID_KEYBOARD_ENTER);
    
    else if (data == 0x000000330000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(50);

      Keyboard.println("https://youtube.com/");
    }
    else if (data == 0x000000220000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_ALT);
      Keyboard.press(HID_KEYBOARD_TAB);
      Keyboard.releaseAll();
    }
    else if (data == 0x0000000F0000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_GUI);
      Keyboard.press(HID_KEYBOARD_TAB);
      Keyboard.releaseAll();
    }

    else if (data == 0x0000001C0000000E) Mouse.move(0, -5); //up
    else if (data == 0x000000130000000E) Mouse.move(-5, 0); //left
    else if (data == 0x0000001D0000000E) Mouse.move(0, 5); //down
    else if (data == 0x000000120000000E) Mouse.move(5, 0); //right
    else if (data == 0x000000250000000E) Mouse.click(MOUSE_LEFT);
    else if (data == 0x0000003B0000000E) Mouse.click(MOUSE_RIGHT);
    
    IrReceiver.resume(); // Enable receiving of the next value

  }
}
