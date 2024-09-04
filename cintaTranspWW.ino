#include <Servo.h>
#include <Adafruit_NeoPixel.h>


//NeoPixel Tira de Led Cinta Transp Selectora
// Defino el pin donde esta conectada la tira de led de la cinta
#define pinLedSemaforo        12 

// Defino la cantidad de leds
#define NUMPIXELS 8 // Tira de 8 leds
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

//defino el objeto semaforo para encender los leds
Adafruit_NeoPixel semaforo(NUMPIXELS, pinLedSemaforo, NEO_GRB + NEO_KHZ800); 


//Servomotor
Servo selector;  // crea el objeto para manejar el SERVO SG90
int posOK = 100;// posicion del servo sin barrera
int posMetal=130; //posición del servo con barrera bloqueando

//DRIVER MOTOR L298N MOTOR A cinta transportadora de ladrillos
int velocidadCinta2=255; //Salida PWM al Enable del driver L298D para controlar la velocidad del motor
int INA=11; // Pin para definir el sentido de giro de la cinta
int INB=10; // Pin para definir el sentido de giro de la cinta
int PinEnA=9; //Pin al EnableB del Driver L298N para controlar la velocidad

//DRIVER MOTOR L298N MOTOR B Cinta transportadora de materiales
int velocidadCinta=255; //Salida PWM al Enable del driver L298D para controlar la velocidad del motor
int INC=4; // Pin para definir el sentido de giro de la cinta
int IND=2; // Pin para definir el sentido de giro de la cinta
int PinEnB=3; //Pin al EnableB del Driver L298N para controlar la velocidad

//Sensor de Metales
int pinSensor=8;
int lecturaSensor;

void setup() {
  //Inicio el servomotor
  selector.attach(6);  // vincula el servo que usamos para el selector de objetos al pin digital 6
  selector.write(posOK); // Posiciona el selector en 0 grados
  delay(150);
  selector.detach();
  
  delay(15); //Espera a que el servo llegue a la posición

  Serial.begin(9600);
  //pinMode ( 19 , OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(pinSensor,INPUT); //Defino el pin de entrada para leer el sensor

  //Motor B
  pinMode(velocidadCinta,OUTPUT); //Defino el pin como salida para activar la cinta transportadora
  pinMode(INC,OUTPUT); //Defino como salida el pin para controlar el sentido de giro
  pinMode(IND,OUTPUT); //Defino como salida el pin para controlar el sentido de giro

  //Motor A
  pinMode(velocidadCinta2,OUTPUT); //Defino el pin como salida para activar la cinta transportadora
  pinMode(INA,OUTPUT); //Defino como salida el pin para controlar el sentido de giro
  pinMode(INB,OUTPUT); //Defino como salida el pin para controlar el sentido de giro

  semaforo.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  semaforo.clear(); // Set all pixel colors to 'off'

  inicioLed();
  

}

void loop() {
    
    //Prendo el semaforo en verde
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      semaforo.setPixelColor(i, semaforo.Color(0, 150, 0));
      semaforo.show();   // Send the updated pixel colors to the hardware.
    }

    //Comienza a girar la cinta haciendo colocando el PWM y el sentido de giro del Motor B
    analogWrite(PinEnB, velocidadCinta); //PWM
    digitalWrite(INC,HIGH); //Sentido de giro
    digitalWrite(IND,LOW); //Sentido de giro

    //Comienza a girar la cinta haciendo colocando el PWM y el sentido de giro del Motor A
    analogWrite(PinEnA, velocidadCinta2); //PWM
    digitalWrite(INA,HIGH); //Sentido de giro
    digitalWrite(INB,LOW); //Sentido de giro
   

    //Leo el estado del sensor de metales
    lecturaSensor=digitalRead(pinSensor);
    
    
    if(lecturaSensor==LOW) //Si el pinSensor está en LOW es porque detecto un metal
    {
        //Prendo semaforo en rojo
        for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
          semaforo.setPixelColor(i, semaforo.Color(150, 0, 0));
          semaforo.show();   // Send the updated pixel colors to the hardware.
        }
        //Activo el servo y lo desvio por 4 segundos
          selector.attach(6);//Prendo el servo 
          selector.write(posMetal); //Lo muevo a la posicion de bloqueo
          delay(4000); //Espero 4 segundos
        //Vuelvo el servo a la posicion normal y lo apago
          selector.write(posOK); //Muevo el servo a la posicion normal
          delay(150); //Espero 150 milisegundos
          selector.detach(); //Desconecto el servo
        

    }

}

//Esta funcion hace el juego de led del inicio
void inicioLed(){

     //Configuro tira en verde para q prenda de a 1 pixel
     for(int i=0; i<NUMPIXELS; i++) { 
      semaforo.setPixelColor(i, semaforo.Color(0, 150, 0));
      semaforo.show();   // Send the updated pixel colors to the hardware.
      delay(DELAYVAL); // Pause before next pass through loop
    }
    //Configuro tira en rojo para q prenda de a 1 pixel
    for(int i=0; i<NUMPIXELS; i++) { 
      semaforo.setPixelColor(i, semaforo.Color(150, 0, 0));
      semaforo.show();   // Send the updated pixel colors to the hardware.
      delay(DELAYVAL); // Pause before next pass through loop
  }
    //Configuro toda tira en verde
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      semaforo.setPixelColor(i, semaforo.Color(0, 150, 0));
    }
    //Enciendo verde
    semaforo.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop

    //Configuro toda la tira en verde
    for(int i=0; i<NUMPIXELS; i++) { 
    semaforo.setPixelColor(i, semaforo.Color(150, 0, 0));
    }  
    //Enciendo en verde
    semaforo.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop

    //Configuro toda la tira en rojo
    for(int i=0; i<NUMPIXELS; i++) { 
    semaforo.setPixelColor(i, semaforo.Color(150, 0, 0));
    }  
    //Enciendo en rojo
    semaforo.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop

    //Configuro Bandera de Arg

    //Tres led en celeste
    for(int i=0; i<=2; i++) { 
    semaforo.setPixelColor(i, semaforo.Color(0, 0, 200));
    }  
    //Dos led en blanco
    for(int i=3; i<=4; i++) { // For each pixel...
    semaforo.setPixelColor(i, semaforo.Color(255, 255, 255));
    }
    //Tres led en celeste
    for(int i=5; i<=7; i++) {
    semaforo.setPixelColor(i, semaforo.Color(0, 0, 200));
    }
    //Enciendo bandera de Arg
    semaforo.show();   
    delay(DELAYVAL); 
  
  }
