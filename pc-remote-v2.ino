#define DECODE_NEC
#define DECODE_RC5
//#define DECODE_RC6
#define NO_LEGACY_COMPATIBILITY
#define IR_RECEIVE_PIN 5

#include <IRremote.h>
#include "HID-Project.h"
#define code_index_length 36
uint64_t code_index[code_index_length]={
0x000000100000000E,
0x000000110000000E,
0x0000000D0000000E,
0x000000320000000E,
0x0000003E0000000E,
0x000000260000000E,
0x000000200000000E,
0x000000210000000E,
0x000000060000000E,
0x000000020000000E,
0x000000040000000E,
0x000000080000000E,
0x000000050000000E,
0x0000000C0000000E,
0x000000330000000E,
0x000000220000000E,
0x0000000F0000000E,
0x0000003C0000000E,
0x000000030000000E,
0x000000090000000E,
0x0000001C0000000E,
0x0000000700040007,
0x0000001D0000000E,
0x000000120000000E,
0x000000250000000E,
0x0000003B0000000E,
0x0000009500040007,
0x000000240000000E,
0x0000000C0000000E,
0x0000002100040007,
0x0000003900040007,
0x000000F000040007,
0x0000004500040007,
0x000000380000000E,
0x000000340000000E,
0x000000370000000E
};

uint32_t current_event_time=0, last_event_time=0, last_data_time=0, last_execution_time=0;
uint64_t current_event_code=0, last_event_code=0;
uint8_t current_event_button_state=0, last_event_button_state=0;

uint8_t repeat_action=0;

uint8_t logarithmic_delay_run(uint32_t max_delay, uint32_t speed=50000){
  if ( ((millis()-last_execution_time)>(millis()-current_event_time)) || (millis()-last_execution_time) > min(speed/(millis()-current_event_time), max_delay)){
              last_execution_time=millis();
              return 1;
  }
  return 0;
}


void button_press(){
//  Serial.println("BUTTON DOWN!");
    repeat_action=0;

    if (current_event_code == 0x000000100000000E) {
      if (logarithmic_delay_run(250)) Consumer.write(MEDIA_VOLUME_UP);
      repeat_action=1;
    }
    else if (current_event_code == 0x000000110000000E) {
      if (logarithmic_delay_run(250)) Consumer.write(MEDIA_VOLUME_DOWN);
      repeat_action=1;
    }
    else if (current_event_code == 0x0000000D0000000E) Consumer.write(MEDIA_VOLUME_MUTE);
    else if (current_event_code == 0x000000320000000E) Consumer.write(MEDIA_PLAY_PAUSE);
    else if (current_event_code == 0x000000340000000E) Consumer.write(MEDIA_NEXT);
    else if (current_event_code == 0x000000370000000E) Consumer.write(MEDIA_PREVIOUS);
    else if (current_event_code == 0x0000003E0000000E) Consumer.write(CONSUMER_BROWSER_HOME);

    else if (current_event_code == 0x000000260000000E) Keyboard.write(HID_KEYBOARD_ESCAPE);
    else if (current_event_code == 0x000000200000000E) Keyboard.write(HID_KEYBOARD_PAGE_UP);
    else if (current_event_code == 0x000000210000000E) Keyboard.write(HID_KEYBOARD_PAGE_DOWN);
    
    else if (current_event_code == 0x000000060000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_RIGHTARROW); repeat_action=1; }
    else if (current_event_code == 0x000000020000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_UPARROW); repeat_action=1; }
    else if (current_event_code == 0x000000040000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_LEFTARROW); repeat_action=1; }
    else if (current_event_code == 0x000000080000000E) { if (logarithmic_delay_run(250)) Keyboard.write(HID_KEYBOARD_DOWNARROW); repeat_action=1; }
    else if (current_event_code == 0x000000050000000E) Keyboard.write(HID_KEYBOARD_ENTER);
    
    else if (current_event_code == 0x000000240000000E) Keyboard.write(HID_KEYBOARD_F11);
    else if (current_event_code == 0x000000F000040007) Keyboard.write(HID_KEYBOARD_F5);
    else if (current_event_code == 0x0000004500040007) Keyboard.write(HID_KEYBOARD_LEFT_ALT);

    else if (current_event_code == 0x0000009500040007) System.write(HID_SYSTEM_SLEEP);
    
    else if (current_event_code == 0x000000330000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(50);

      Keyboard.println("https://youtube.com/");
    }
    else if (current_event_code == 0x000000220000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_ALT);
      Keyboard.press(HID_KEYBOARD_TAB);
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x0000000F0000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_GUI);
      Keyboard.press(HID_KEYBOARD_TAB);
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x0000003C0000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_GUI);
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press('o');
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x000000030000000E) {
      if (logarithmic_delay_run(250)) {
        Keyboard.press(HID_KEYBOARD_LEFT_ALT);
        Keyboard.press(HID_KEYBOARD_PAGE_UP);
        Keyboard.release(HID_KEYBOARD_PAGE_UP);
        Keyboard.releaseAll();
      }
      repeat_action=1;
    }
    else if (current_event_code == 0x000000090000000E) {
      if (logarithmic_delay_run(250)) {
        Keyboard.press(HID_KEYBOARD_LEFT_ALT);
        Keyboard.press(HID_KEYBOARD_PAGE_DOWN);
        Keyboard.release(HID_KEYBOARD_PAGE_DOWN);
        Keyboard.releaseAll();
      }
      repeat_action=1;
    }
    else if (current_event_code == 0x0000000C0000000E) {
        Keyboard.press(HID_KEYBOARD_LEFT_ALT);
        Keyboard.press(HID_KEYBOARD_F4);
        Keyboard.release(HID_KEYBOARD_F4);
        Keyboard.releaseAll();
    }
    else if (current_event_code == 0x0000002100040007) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press(HID_KEYBOARD_PAGE_UP);
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x0000003900040007) {
      Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
      Keyboard.press(HID_KEYBOARD_PAGE_DOWN);
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x000000380000000E) {
      Keyboard.press(HID_KEYBOARD_LEFT_GUI);
      Keyboard.press('l');
      Keyboard.releaseAll();
    }
    else if (current_event_code == 0x0000001C0000000E) { if (logarithmic_delay_run(250, 500)) Mouse.move(0, -1); repeat_action=1; } //up
    else if (current_event_code == 0x0000000700040007) { if (logarithmic_delay_run(250, 500)) Mouse.move(-1, 0); repeat_action=1; } //left
    else if (current_event_code == 0x0000001D0000000E) { if (logarithmic_delay_run(250, 500)) Mouse.move(0,  1); repeat_action=1; } //down
    else if (current_event_code == 0x000000120000000E) { if (logarithmic_delay_run(250, 500)) Mouse.move(1,  0); repeat_action=1; } //right
    else if (current_event_code == 0x000000250000000E) Mouse.click(MOUSE_LEFT);
    else if (current_event_code == 0x0000003B0000000E) Mouse.click(MOUSE_RIGHT);
    else return 0;
    return 1;

}
void button_release(){
//  Serial.println("BUTTON UP!");

  repeat_action=0;
}

void IREventHandler(){
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN){
            IrReceiver.resume();
            return;
    }

    uint64_t new_event_code=0;
    memcpy(&new_event_code, &IrReceiver.decodedIRData, sizeof(IrReceiver.decodedIRData.protocol) + sizeof(IrReceiver.decodedIRData.address) + sizeof(IrReceiver.decodedIRData.command));

    if (new_event_code == current_event_code && current_event_button_state == 1) {//nothing new happend, just a repeat code
      last_data_time=millis();
      IrReceiver.resume();
      return;
    }
	    uint32_t low = new_event_code;
    uint32_t high = (new_event_code >> 32);
    char buf[32];
    sprintf(buf, "0x%08lX%08lX", high, low);
    Serial.println(buf);
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
	int i=0;
	for (i=0; i<code_index_length; i++){
		if (code_index[i] == new_event_code) break;
	}
	if (i==code_index_length) {
            IrReceiver.resume();
            return;
	}

    if (current_event_button_state == 1){
      last_event_time=current_event_time;
      current_event_time=millis();
      
      last_event_code=current_event_code;
      
      last_event_button_state=current_event_button_state;
      current_event_button_state=0;

      button_release();
    }

    last_event_code=current_event_code;
    current_event_code=new_event_code;

    last_event_time=current_event_time;
    current_event_time=millis();
    last_data_time=current_event_time;
    
    last_event_code=current_event_code;
    
    last_event_button_state=current_event_button_state;
    current_event_button_state=1;

    button_press();

    IrReceiver.resume();
  } else if (millis()-last_data_time > 200 && current_event_button_state == 1) {
    last_event_time=current_event_time;
    current_event_time=millis();
    last_event_code=current_event_code;

    last_event_button_state=current_event_button_state;
    current_event_button_state=0;

    button_release();

  }
  
}



void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  IrReceiver.begin(IR_RECEIVE_PIN);

  Mouse.begin();
  Keyboard.begin();
  Consumer.begin();
  System.begin();
  Serial.begin(2000000);
}

void loop() {
  IREventHandler();
  if (repeat_action){
    button_press();
  }

}
