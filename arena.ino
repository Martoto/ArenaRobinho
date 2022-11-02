void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  #define RED 2
  #define GREEN 3
  #define BLUE 4
  
  #define RED_BUTTON 6
  #define GREEN_BUTTON 7
  #define BLUE_BUTTON 8
  #define YELLOW_BUTTON 9

  #define COLOR_READ_TIME 3000 //3s
  #define BUTTON_READ_TIME 10 //*500ms
        
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT); 
  pinMode(BLUE, OUTPUT); 

  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);

  pinMode(RED_BUTTON, INPUT_PULLUP); // Botao 1
  pinMode(GREEN_BUTTON, INPUT_PULLUP); // Botao 2
  pinMode(BLUE_BUTTON, INPUT_PULLUP); // Botao 3
  pinMode(YELLOW_BUTTON, INPUT_PULLUP); // Botao 4

  Serial.begin(9600);
  
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value);
int Read_Buttons();

// the loop function runs over and over again forever
void loop() 
{
  if(Serial.available()) 
  {
    char data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd

    switch (data_rcvd)
    {
      case 'r':  // RED    
        RGB_color(255,0,0);
        delay(COLOR_READ_TIME);
        RGB_color(0,0,0);
        Serial.write('k');
        break;
      case 'g':  // GREEN    
        RGB_color(0,255,0);
        delay(COLOR_READ_TIME);
        RGB_color(0,0,0);
        Serial.write('k');
        break;
      case 'b':   // BLUE    
        RGB_color(0,0,255);
        delay(COLOR_READ_TIME);
        RGB_color(0,0,0);
        Serial.write('k');
        break;
      case 'y':  // YELLOW     
        RGB_color(255,255,0);
        delay(COLOR_READ_TIME);
        RGB_color(0,0,0);
        Serial.write('k');
        break;
      case 'p':  // Botoes
        char button = 0;
        int loop = 0; 
        while (loop < BUTTON_READ_TIME)
        { 
          button = Read_Buttons();          
          if (button == 0)
          {
            loop++;
            delay(500); 
          }
          else
            loop = BUTTON_READ_TIME+5;       
        }
        if (loop == BUTTON_READ_TIME)
          button = 'n';
        Serial.write(button);
        break;
    }
  }                   // wait for a second
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(RED, red_light_value);
  analogWrite(GREEN, green_light_value);
  analogWrite(BLUE, blue_light_value);
}

int Read_Buttons()
{
  if(digitalRead(RED_BUTTON) == 0)
    return 'r';
  else if(digitalRead(GREEN_BUTTON) == 0)
    return 'g';
  else if(digitalRead(BLUE_BUTTON) == 0)
    return 'b';
  else if(digitalRead(YELLOW_BUTTON) == 0)
    return 'y';
  else
    return 0;
} 