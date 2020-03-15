// This is arduino project to build nokia 3310 mobile functionality using the Nokia 5110 LCD module and keypad module.

// firstly include both library for LCD and keypad module.
#include<LCD5110_Graph.h>               // for Nokia 5110 LCD module.
#include<Keypad.h>                      // for keypad module.

const byte ROWS = 4;          // for four rows of keypad.
const byte COLS = 3;          // for three columns of keypad.

char keys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},              // 4*3 keypad layout.
  {'7','8','9'},
  {'S','0','X'}
  };

char rowPins[ROWS] = {7,8,9,10};    // pins for keypad rows from arduino.
char colPins[COLS] = {11,12,13};    // pins for keypad columnns from arduino.

// Creating the keypad object as "sample_keypad".
Keypad sample_keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

// Creating the LCD object as "sample_glcd".
LCD5110 sample_glcd(6,5,4,2,3);       // sample_glcd(SCLK,DIN,DC,RST,SCE)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define flash_led A0            // for flashing led.
#define buzzer A1               // for buzzer.
///////////////////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char SmallFont[];         // for including the SmallFont font style.
extern unsigned char MediumNumbers[];         // for including the MediumNumbers font style.

extern uint8_t screen[];      // for main screen and menu screen.

extern uint8_t smile[];                    // for showing the correctness of entered password.
extern uint8_t sad[];

extern uint8_t setting[];
extern uint8_t gallery[];
extern uint8_t volume[];
extern uint8_t torch[];                    // menu icons images
extern uint8_t internet[];
extern uint8_t games[];
extern uint8_t contrast[];

extern uint8_t cricket[];
extern uint8_t football[];                 // games icons images
extern uint8_t puzzle[];

extern uint8_t iron_man[];
extern uint8_t dragon[];                  // images
extern uint8_t kungfu[];
extern uint8_t english_league[];
///////////////////////////////////////////////////////////////////////////////////////////////////////////

char input_key;                                    // for input or pressed key value.
int page_value = 0;                                // page value for mobile screen.
int app_value = 0;                                 // app value for app menu in mobile.
int ringtone_frequency[13] ={659,587,370,415,554,494,294,330,494,440,370,330,440}; // ringtone music notes frequency.
int setting_value = 0;                             // for setting number.
int volume_value = 10;                              // for volume level setting.       
int contrast_value = 60;                             // for contrast level setting.  
int game_value = 0;                                  // for game selection.     
int internet_value = 0;                              // for selection on and off button for internet accessing. 
int torch_value = 0;                                 // for selection on and off button of torch. 
int image_value = 0;       
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:

pinMode(flash_led,OUTPUT);
pinMode(buzzer,OUTPUT);

sample_glcd.InitLCD(60);             // for initializing the sample lcd.
sample_glcd.setFont(SmallFont);      // setting the font style as "Small Font".
sample_glcd.drawRect(0,0,83,47);
sample_glcd.print("Enter",5,10);
sample_glcd.print("Password:",5,20);
sample_glcd.update();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION 0:
// It is main function for controlling the page of mobile screen.
void main_function(int page_value){                                               // MAIN FUNUCTION.
  switch(page_value){
    case 0:
          password_writing();   
          break;
    case 1:
          home_screen();
          break;
    case 2:
          menu_screen(app_value);
          break;
    case 3:
          inside_app(app_value);
          break;
    case 4:
          inside_inside_app(app_value);
          break;

  }
}
///////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 1:
// password writing.                                                           // PASSWORD WRITING.

void password_writing(){
  
  static int char_number = 20;                  // for counting the number character entering.
  static int correct = 0;                       // for checking password correctness.
  char saved_password[5] = {'1','2','5','8','0'};       //5 characters saved password for entering into mobile functionality.
  char password_key = sample_keypad.getKey();   // returns the pressed keypad key.
  
  if(password_key != NO_KEY){
    sound();
    if(char_number < 50){                             // ENTER THE FIVE CHARACTER PASSWORD.
      sample_glcd.print("*",char_number,33);
      char_number = char_number + 7;
      if (password_key == saved_password[correct]){   // when password key is eqaul to respective saved password key. 
        correct++;                                    // then correctness increases.
      }
    }
    else if (password_key == 'S'){
      password_checking(correct);
    }
 }
  sample_glcd.update();
}
////////////////////////////////////////////////////////////////////////////////

// FUNCTION 2:                                                               // PASSWRORD CHECKING.
// password checking.
void password_checking(int correct){
        
        if(correct == 5){
        sample_glcd.clrScr();
        sample_glcd.print("Correct",CENTER,1);
        sample_glcd.print("Password",CENTER,12);
        sample_glcd.drawBitmap(30,25,smile,20,20); 
        sample_glcd.update();
        delay(1000);                     // after 2 seconds.
        starting();                      // calling starting function.
        page_value = 1;
//        sample_glcd.clrScr();
//        sample_glcd.print("Inside mobile",CENTER,20);
//        sample_glcd.update();
        }
      else{
        sample_glcd.clrScr();
        sample_glcd.print("Wrong",CENTER,1);
        sample_glcd.print("Password",CENTER,12);
        sample_glcd.drawBitmap(30,25,sad,20,20);
        sample_glcd.update();
        delay(1000);
        sample_glcd.clrScr();
        sample_glcd.update();
      }
 }
/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION 3:
// This is function for making the starting display.                    // STARTING ANIMATION FUNCTION.
void starting(){
  sample_glcd.clrScr();
  sample_glcd.drawRect(0, 0, 83, 47);
  for (int i=0; i<48; i+=4)
  { 
    sample_glcd.drawLine(0, i, i*1.75, 47);
    sample_glcd.update(); 
    int freq = i / 8;
    tone(buzzer,ringtone_frequency[freq]);                                  // for making the ringtone.
    delay(150);
  }
  for (int i=0; i<48; i+=4)
  {
    sample_glcd.drawLine(83, 47-i, 83-(i*1.75), 0);
    sample_glcd.update();
    int freq = i / 8;                                                    // for making the ringtone.
    tone(buzzer,ringtone_frequency[freq + 6]);
    delay(150);
  }
  tone(buzzer,ringtone_frequency[12]);                   
  delay(400);                             
  noTone(buzzer);                                                       // stoping the ringtone sound.
  delay(1000);   // delay of 1 second
  sample_glcd.print("NOKIA",CENTER,15);   // printing the string "NOKIA 3310" on screen.
  sample_glcd.print("3310",CENTER,24);
  sample_glcd.update();
  delay(3000);     // delay of 3 seconds
  sample_glcd.clrScr();
  sample_glcd.update();
}
/////////////////////////////////////////////////////////////////////////////

//FUNCTION 4:                                                      // SOUND FUNCTION FOR BUZZER.
// for generating bip sound when any key pressed on keypad.
void sound(){
  digitalWrite(buzzer,HIGH);
  delay(10);
  digitalWrite(buzzer,LOW);
}
/////////////////////////////////////////////////////////////////////////////

// FUNCTION 5:
// This is function for showing the main screen.
void home_screen(){                                                // HOME SCREEN FUNCTION.
  sample_glcd.clrScr();
  sample_glcd.drawBitmap(0,0,screen,84,48);
  sample_glcd.print("NOKIA",CENTER,15);
  sample_glcd.print("Menu",CENTER,38);
  sample_glcd.drawLine(0,47,83,47);
  sample_glcd.update(); 
  char input_key = sample_keypad.getKey();
  if (input_key != NO_KEY){                 // when key pressed.
    sound();
    if (input_key == 'S'){                 // if selection key was pressed.
      page_value = 2;                      // go to menu screen.
    }
  }
}
/////////////////////////////////////////////////////////////////////////////


// FUNCTION 6:
// This is function for showing the menu screen.
void menu_screen(int icon_number){                                                        // MENU SCREEN
  switch(icon_number){
    case 0:  
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,setting,30,30);      // SETTING ICON
          sample_glcd.print("Setting",CENTER,5);
          sample_glcd.update();
          break;
    case 1:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,volume,30,30);      // VOLUME ICON
          sample_glcd.print("Volume",CENTER,5);
          sample_glcd.update();
          sample_glcd.clrScr();
          break;
    case 2:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,contrast,30,30);      // CONTRAST ICON
          sample_glcd.print("Contrast",CENTER,5);
          sample_glcd.update();
          break;
    case 3:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,games,30,30);      // GAMES ICON
          sample_glcd.print("Games",CENTER,5);
          sample_glcd.update();
          break;
    case 4:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,internet,30,30);      // INTERNET ICON
          sample_glcd.print("Internet",CENTER,5);
          sample_glcd.update();
          break;
    case 5:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,torch,30,30);      // TORCH ICON
          sample_glcd.print("Torch",CENTER,5);
          sample_glcd.update();
          break;
    case 6:
          sample_glcd.clrScr();
          sample_glcd.drawBitmap(0,0,screen,84,48);        
          sample_glcd.drawBitmap(30,15,gallery,30,30);      // GALLERY ICON
          sample_glcd.print("Gallery",CENTER,5);
          sample_glcd.update();
          break;
  }
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){                          // when key is pressed.
    sound();
    if(input_key == 'S'){                           // if selection key pressed.
      page_value = 3;                               // go inside app.
    }
    else if(input_key == 'X'){                      // if exit key pressed.
      page_value = 1;                               // back to home screen.
    }
    else if(input_key == '6'){                      // if right key pressed.
      app_value++;                                  // then scroll right happen.
      if(app_value > 6){
        app_value = 0;
      }
    }
    else if(input_key == '4'){                         // if left key was pressed.
      app_value--;                                     // Left scroll happen.
      if(app_value < 0){
        app_value = 6;
      }
    }
  }

}
/////////////////////////////////////////////////////////////////////////////

//FUNCTION 7:                                                                     // INSIDE APP FUNCTIONALITY
// This is function for showing functionality of apps in menu.
void inside_app(int app_number){                           
  switch(app_number){
    case 0:
          inside_setting(setting_value);                           
          break;

    case  1:
          inside_volume();
          break;

    case 2:
          inside_contrast();
          break;

    case 3:
          inside_games(game_value);
          break;

    case 4:
          inside_internet(internet_value);
          break;

    case 5:
          inside_torch(torch_value);
          break;
    
    case 6:
          inside_gallery(image_value);
          break;
     
  }
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTION 8:
// for inside setting app functionality.

void inside_setting(int s){
  switch(s){
    case 0:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Setting",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Language   ",3,18);
          sample_glcd.print("2.Storage    ",3,28);
          sample_glcd.print("3.Fontsize   ",3,37);
          sample_glcd.update();
          break;
    case 1:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Setting",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.invertText(true);
          sample_glcd.print("1.Language   ",3,18);
          sample_glcd.invertText(false);
          sample_glcd.print("2.Storage    ",3,28);
          sample_glcd.print("3.Fontsize   ",3,37);
          sample_glcd.update();
          break;
   case 2:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Setting",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Language   ",3,18);
          sample_glcd.invertText(true);
          sample_glcd.print("2.Storage    ",3,28);
          sample_glcd.invertText(false);
          sample_glcd.print("3.Fontsize   ",3,37);
          sample_glcd.update();
          break;
    case 3:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Setting",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Language   ",3,18);
          sample_glcd.print("2.Storage    ",3,28);
          sample_glcd.invertText(true);
          sample_glcd.print("3.Fontsize   ",3,37);
          sample_glcd.invertText(false);
          sample_glcd.update();
          break;    
  }

  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == '8'){
      setting_value++;
      if(setting_value > 3){
        setting_value = 1;
      }
    }

    else if(input_key == '2'){
      setting_value--;
      if(setting_value < 1){
        setting_value = 3;
        }
      }
    }
  }


/////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 9:
// for inside inside setting app.

void inside_inside_setting(){
  sample_glcd.clrScr();  
  sample_glcd.print("Inside",CENTER,3);               
  sample_glcd.print("Inside",CENTER,13);                    // INSIDE SETTING.
  sample_glcd.print("Setting",CENTER,23);           
  sample_glcd.update();
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 3;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 10:
// for inside volume app functionality.

void inside_volume(){           // input volume value as 'v'. 
//  sample_glcd.clrScr();
  sample_glcd.print("Volume",CENTER,3);
  sample_glcd.drawLine(10,12,73,12);
  sample_glcd.print("-",0,30);
  sample_glcd.print("+",76,30);
  sample_glcd.drawRoundRect(9,25,71,40);
  sample_glcd.update();
  
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    
    if(input_key == 'X'){
      page_value = 2;
    }
    
    else if(input_key == '6' & volume_value < 70 ){
      for(int i = volume_value; i <= volume_value + 11; i++){
         sample_glcd.drawLine(i,25,i,40);
         sample_glcd.update();  
      }
      volume_value = volume_value + 12; 
      if(volume_value > 69){
        volume_value = 70;
      }
    }

    else if(input_key == '4'){
       for(int i = volume_value; i >= volume_value - 11; i--){
         sample_glcd.clrLine(i,25,i,40);
         sample_glcd.update();  
       }
       volume_value = volume_value - 12; 
       if(volume_value < 10){
         volume_value = 10;
      }
    }

    else if(input_key == 'S'){
      page_value = 4;
    }
}
}
///////////////////////////////////////////////////////////////////////////////////
// FUNCTION 11:
// for inside contrast app functionality.
void inside_contrast(){
  sample_glcd.clrScr();
  sample_glcd.print("Contrast",CENTER,3);
  sample_glcd.drawLine(10,15,73,15);
  sample_glcd.drawBitmap(2,20,contrast,30,30);
  sample_glcd.setFont(MediumNumbers);
  sample_glcd.printNumI(contrast_value,50,25);
  sample_glcd.setFont(SmallFont);
  sample_glcd.update();
  sample_glcd.setContrast(contrast_value);
   char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == '8'){
      contrast_value = contrast_value - 2;
      if(contrast_value < 40){
        contrast_value = 30;
      }
    }
    else if(input_key == '2'){
      contrast_value = contrast_value + 2;
      if(contrast_value > 80){
        contrast_value = 80;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 12:
// for inside games app functionality.
void inside_games(int g){
  switch(g){
    case 0:
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(0,0,screen,84,48);
           sample_glcd.print("Football",CENTER,3);
           sample_glcd.drawBitmap(30,15,football,30,30);
           sample_glcd.update();
           break;
    case 1:
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(0,0,screen,84,48);
           sample_glcd.print("Cricket",CENTER,3);
           sample_glcd.drawBitmap(30,15,cricket,30,30);
           sample_glcd.update();
           break;
    case 2:
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(0,0,screen,84,48);
           sample_glcd.print("Puzzle",CENTER,3);
           sample_glcd.drawBitmap(30,15,puzzle,30,30);
           sample_glcd.update();
           break;
  }
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == '6'){
      game_value++;
      if(game_value > 2){
        game_value = 0;
      }
    }
    else if(input_key == '4'){
      game_value--;
      if(game_value < 0){
        game_value = 2;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// FUNCTION 13:
// for inside internet app functionality.
void inside_internet(int i){
  switch(i){
    case 0:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Internet",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.update();
          break;
    case 1:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Internet",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.invertText(true);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.invertText(false);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.update();  
          break;
    case 2:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Internet",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.invertText(true);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.invertText(false);
          sample_glcd.update(); 
          break;  
  }
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == '8'){
      internet_value = 2;
    }
    else if(input_key == '2'){
      internet_value = 1;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// FUNCTION 14:
// for inside Torch app functionality.
void inside_torch(int t){
  switch(t){
    case 0:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Torch",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.update();
          break;
    case 1:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Torch",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.invertText(true);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.invertText(false);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.update();  
          digitalWrite(flash_led,HIGH);
          break;
    case 2:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Torch",CENTER,3);
          sample_glcd.drawLine(10,15,73,15);
          sample_glcd.print(" ON ",CENTER,23);
          sample_glcd.invertText(true);
          sample_glcd.print(" OFF ",CENTER,35);
          sample_glcd.invertText(false);
          sample_glcd.update();
          digitalWrite(flash_led,LOW); 
          break;  
  }
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == '8'){
      torch_value = 2;
    }
    else if(input_key == '2'){
      torch_value = 1;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 15:
// for inside gallery app functionality.
void inside_gallery(int im){
  switch(im){
    case 0:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Gallery",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Image1     ",3,18);
          sample_glcd.print("2.Image2     ",3,28);
          sample_glcd.print("3.Image3     ",3,37);
          sample_glcd.update();
          break;
    case 1:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Gallery",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.invertText(true);
          sample_glcd.print("1.Image1     ",3,18);
          sample_glcd.invertText(false);
          sample_glcd.print("2.Image2     ",3,28);
          sample_glcd.print("3.Image3     ",3,37);
          sample_glcd.update();
          break;
   case 2:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Gallery",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Image1     ",3,18);
          sample_glcd.invertText(true);
          sample_glcd.print("2.Image2     ",3,28);
          sample_glcd.invertText(false);
          sample_glcd.print("3.Image3   ",3,37);
          sample_glcd.update();
          break;
    case 3:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Gallery",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Image1   ",3,18);
          sample_glcd.print("2.Image2   ",3,28);
          sample_glcd.invertText(true);
          sample_glcd.print("3.Image3   ",3,37);
          sample_glcd.invertText(false);
          sample_glcd.update();
          break; 
    case 4:
          sample_glcd.clrScr();
          sample_glcd.drawRect(0,0,83,47);
          sample_glcd.print("Gallery",CENTER,3);
          sample_glcd.drawLine(10,13,73,13);
          sample_glcd.print("1.Image2   ",3,18);
          sample_glcd.print("2.Image3   ",3,28);
          sample_glcd.invertText(true);
          sample_glcd.print("3.Image4   ",3,37);
          sample_glcd.invertText(false);
          sample_glcd.update();
          break;  
  }

  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 2;
    }
    else if(input_key == 'S'){
      page_value = 4;
    }
    else if(input_key == '8'){
      image_value++;
      if(image_value > 4){
        image_value = 1;
      }
    }

    else if(input_key == '2'){
      image_value--;
      if(image_value < 1){
        image_value = 4;
        }
      }
    }
  }
////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION 16:
// for more inside app functionality.
void inside_inside_app(int ap){
  switch(ap){
    case 0:
          // inside_inside_setting(setting_value);
          break;
    case 6:
          inside_inside_gallery(image_value);
          break;
  }
}

/////////////////////////////////////////////////////////////////////////////
// FUNCTION 17:
// for more inside setting app functionality.
//void inside_inside_setting(int set){
//  
//}
////////////////////////////////////////////////////////////////////////////
// FUNCTION 18:
// for more inside gallery app functionality.
void inside_inside_gallery(int im){
  switch(im){
    case 1 :
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(20,0,iron_man,50,50);
           sample_glcd.drawRect(2,0,20,1);
           sample_glcd.update();
           break;
    case 2 :
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(20,0,dragon,50,50);
           sample_glcd.drawRect(21,0,40,1);
           sample_glcd.update();
           break;
    case 3 :
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(20,0,kungfu,50,50);
           sample_glcd.drawRect(41,0,60,1);
           sample_glcd.update();
           break;
    case 4 :
           sample_glcd.clrScr();
           sample_glcd.drawBitmap(20,0,english_league,50,50);
           sample_glcd.drawRect(61,0,80,1);
           sample_glcd.update();
           break;
  }
  char input_key = sample_keypad.getKey();
  if(input_key != NO_KEY){
    sound();
    if(input_key == 'X'){
      page_value = 3;
    }
    else if(input_key == '6'){
      image_value++;
      if(image_value > 4){
        image_value = 1;
      }
    }

    else if(input_key == '4'){
      image_value--;
      if(image_value < 1){
        image_value = 4;
        }
      }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  // put your main code here, to run repeatedly:
main_function(page_value);
}
