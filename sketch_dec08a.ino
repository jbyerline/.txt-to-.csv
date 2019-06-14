/////////////////////////////////////////////////////////////////////////////
// Symbolic Constants
#define LED0 11
#define LED1 9
#define LED2 6
#define LED3 3

#define SW0 12
#define SW1 8
#define SW2 7
#define SW3 4
#define TEMP A0
#define POT A1
#define LIGHT A2

#define ANAINMAX  1023
#define ANAOUTMAX 100.0
#define BAUD 9600

#define SAMPLES 250

#define MEASUREDELAY 20

/////////////////////////////////////////////////////////////////////////////
// setup
void setup()
{
  pinMode( LED0, OUTPUT );
  pinMode( LED1, OUTPUT );
  pinMode( LED2, OUTPUT );
  pinMode( LED3, OUTPUT );
  
  pinMode( SW0,   INPUT_PULLUP );
  pinMode( SW1,   INPUT_PULLUP );
  pinMode( SW2,   INPUT_PULLUP );
  pinMode( SW3,   INPUT_PULLUP );
  pinMode( TEMP,  INPUT );
  pinMode( POT,   INPUT );
  pinMode( LIGHT, INPUT );
  
  Serial.begin( BAUD ); 
  
}

/////////////////////////////////////////////////////////////////////////////
// loop
void loop()
{
  int switch0 = 0;
  int switch1 = 0;
  int switch2 = 0;
  int switch3 = 0;
  
  float temperature = 0.0;
  float pot = 0.0;
  float light = 0.0;
  
  static int counter = 0;
  int time_passed = 0;
  int temp;
  
  wait_for_start(); 
  
  for( counter = 0; counter < SAMPLES; counter++ )
  {
    switch0 = read_switches( SW0 );
    switch1 = read_switches( SW1 );
    switch2 = read_switches( SW2 );
    switch3 = read_switches( SW3 );
    pot = read_pot( POT );
    temperature = read_temp( TEMP );
    light = read_light( LIGHT );

    print_stats( switch0, switch1, switch2, switch3, pot, temperature, light, MEASUREDELAY, counter);
   
    
    delay(MEASUREDELAY);
  }
  
  mark_end();
}

/////////////////////////////////////////////////////////////////////////////
// wait_for_start
// Waits for a keypress in the Serial window
void wait_for_start()
{
  Serial.print("Press and release switch 0\n");
  while( digitalRead(SW0) == HIGH ) {
    
    
    }

  Serial.print("Release switch 0\n");
  while(digitalRead(SW0) == LOW ) {
    
    
    }
    Serial.print("---------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////
// read_switches
// Reads the state of the four switches and updates passed in variables
int read_switches( int switch_x )
{
  int switch_read;
  
  if ( digitalRead( switch_x ) == LOW )
  {
    return switch_read = 1;
  }
  else
  {
    return switch_read = 0;
  }
}

/////////////////////////////////////////////////////////////////////////////
// read_pot
// Reads the potentiometer and returns its value as a percentage of the range
float read_pot( int port )
{
  float pot = analogRead( port );
  pot =map(pot, 0, ANAINMAX, 0, ANAOUTMAX);
  return pot/100.0;
}

/////////////////////////////////////////////////////////////////////////////
// read_temp
// Reads the temp sensor and returns its value as a percentage of the range
float read_temp( int port )
{
  float temperature = analogRead( port );
  temperature =map(temperature, 0, ANAINMAX, 0, ANAOUTMAX);
  return temperature/100.0;
}

/////////////////////////////////////////////////////////////////////////////
// read_light
// Reads the light sensor and returns its value as a percentage of the range
float read_light( int port )
{
  float light = analogRead( port );
  light =map(light, 0, ANAINMAX, 0, ANAOUTMAX);
  return light/100.0;
}


/////////////////////////////////////////////////////////////////////////////
// print_stats
// prints settings to console window
void print_stats( int switch0, int switch1, int switch2, int switch3, 
                  float pot, float temperature, float light, 
                  int x, int counter )
{

  Serial.print("time:  ");
  Serial.print(counter * MEASUREDELAY);
  Serial.print(" ms\n");

  Serial.print("potentiometer: ");
  Serial.print(pot);
  Serial.print("\n");

  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.print("\n"); 
  
  Serial.print("light: ");
  Serial.print(light);
  Serial.print("\n");
  
  Serial.print("switch0: ");
  Serial.print(switch0);
  Serial.print("\n");
  
  Serial.print("switch1: ");
  Serial.print(switch1);
  Serial.print("\n"); 
  
  Serial.print("switch2: ");
  Serial.print(switch2);
  Serial.print("\n");
  
  Serial.print("switch3: ");
  Serial.print(switch3);
  Serial.print("\n");
  
  Serial.print("---------------------------\n");
  
  // a command is missing here.  Roughly how often does this run?  How does
  // that relate to the time?

  

}

/////////////////////////////////////////////////////////////////////////////
// mark_end
// marks the end of a run
int mark_end()
{
  Serial.print("ENDENDENDENDENDENDENDENDENDENDENDENDENDEND\n");
}
