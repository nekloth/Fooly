/* *******************************************************
 * 
 *  FOOLY
 *
 *  http://wiki.zgur.net/index.php/fooly
 *
 * ****************************************************** /
#include <Servo.h> 


//Le servo moteur
Servo myservo;

//Les connections à l'Arduino
const int  buttonPin = 2;
const int  pulseServo = 9;
int buttonState = 0;


//Calibrage du servo moteur
int positionMin = 50;
int positionAttente = 120;
int positionMax = 170;

//Variables de temporisation diverses
int vitesseSortiePartie1 = 8;   //Vitesse de "sortie" du bras. Plus la valeur est petite, plus la vitesse sera grande.
int vitesseSortiePartie2 = 1;   //Vitesse de "sortie" du bras. Plus la valeur est petite, plus la vitesse sera grande.
int vitesseRentree = 1;         //Vitesse de "rentrée" du bras. Plus la valeur est petite, plus la vitesse sera grande.

int delaisAvantDeBouger = 500;    //Latence avant de bouger
int delaisAttente = 1000;            //Pause à mi-chemin
int delaisAvantDeRentrer = 100;   // Bras en extension, combien de temps on attend avant de rentrer
void setup() 
{ 
  pinMode(buttonPin, INPUT);
  myservo.attach(pulseServo);
  myservo.write(positionMin);
} 

void loop() {
  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
      delay(delaisAvantDeBouger);

      for (int i=positionMin; i<positionMax; i=i+1) {

        if (i == positionAttente) delay(delaisAttente); //Quand on est à mi-course, on fait une petite pause

        myservo.write(i);

        if (i<positionAttente) {
            delay(vitesseSortiePartie1);
        } else {
            delay(vitesseSortiePartie2);
        }

      }
    
    delay(delaisAvantDeRentrer);
    
    for (int i=positionMax; i>positionMin; i=i-1) {
      myservo.write(i);
      delay(vitesseRentree);
    }
  }

} 
