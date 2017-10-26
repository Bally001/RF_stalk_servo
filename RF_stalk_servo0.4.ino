
    #include <Servo.h>
    #include <IRremote.h>

    unsigned long buttonPress = 0xFFA857; // button on control transmits FFA857

    int RECV_PIN = 11;
    IRrecv irrecv(RECV_PIN);
    decode_results results;

    Servo RF_servo;
    int pos;         // variable to store the servo position

    void setup() {             
    Serial.begin(9600);

    irrecv.enableIRIn(); // Start the receiver
    
    RF_servo.attach(10); // attach servo to digital pin 10
    
    pos = 0;       
    RF_servo.write(pos);  // start RF stalk up
    }

    void loop() {
    pos = RF_servo.read();
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
       }

    if  (results.value == buttonPress) {
    RF_servo.attach(10);
    delay(100);

      if (pos == 89) {
        for(pos = 89; pos >= 0; pos--)  
        {                                  
        RF_servo.write(pos);               
        delay(15);                   
        } 
      }
    
      if  (pos == 0) {
        for(pos = 0; pos <= 89; pos++)    
        {                                
        RF_servo.write(pos);           
        delay(15);       
        } 
      }
      
     delay(100);
     RF_servo.detach();
     delay(500);
      }  
    }
