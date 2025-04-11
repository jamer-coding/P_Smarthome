#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Ajout de l'écran LCD (situé à l'adresse 0x27 écran de 16 caractères et 2 lignes) comme référence dans le code

const int motionPin = 9;          // Le pin du détecteur de mouvement
const int ledMotionPin = 4;       // Le pin de la lampe LED

const int buttonLedPin = 7;       // Le pin du bouton relié à une LED
const int ledButtonPin = 2;       // Le pin de la lampe LED relié à un bouton

const int buttonBuzzerPin = 10;   // Le pin du bouton relié au buzzer
const int buzzerButtonPin = 8;    // Le pin du buzzer relié au bouton

int buttonLedPressed = HIGH;      // Variable utilisé pour un détecteur de mouvement qui controle une LED
int motionDetected = LOW;         // Variable utilisé pour un bouton qui controle une LED
int buttonBuzzerPressed = HIGH;    // Variable utilisé pour un bouton qui controle un buzzer 

void setup() {
  // Initialisation de l'écran LCD
  lcd.init();

  // Setup scénario 1
  pinMode(motionPin, INPUT);
  pinMode(ledMotionPin, OUTPUT);

  // Setup scénario 2
  pinMode(buttonLedPin, INPUT);
  pinMode(ledButtonPin, OUTPUT);

  // Setup scénario 3
  pinMode(buttonBuzzerPin, INPUT);
  pinMode(buzzerButtonPin, OUTPUT);
}


void Get_Values() {
  // Lecture du signal du détecteur de mouvement qui controle une LED
  motionDetected = digitalRead(motionPin);

  // Lecture du signal du bouton qui controle une LED
  buttonLedPressed = digitalRead(buttonLedPin);

  // Lecture du signal du bouton qui controle un buzzer
  buttonBuzzerPressed = digitalRead(buttonBuzzerPin);
}

void Update_States() {
  // Vérification if pour toutes les valeurs

  // Scénario 2
  if (buttonLedPressed == LOW) {
    // Allumer la LED
    digitalWrite(ledButtonPin, HIGH);
  }
  // Scénario 3
  if (buttonBuzzerPressed == LOW) {
    // Activer le buzzer (pin, fréquence en Hz, durée en ms)
    tone(buzzerButtonPin, 200, 1000);
  }
  // Scénario 1
  if (motionDetected == HIGH) {
    // Allumer la LED
    digitalWrite(ledMotionPin, HIGH);
  }
}

void Screen_Output() {
  // Effacer l'écran
  lcd.clear();

  // Vérification if else pour toutes les valeurs

  // Scénario 2
  if (buttonLedPressed == LOW) {
    // Afficher un message
    lcd.backlight();

    // Ajouter un message
    lcd.print("Que la lumiere");

    // Changer la position du curseur
    lcd.setCursor(0, 1);

    // Ajouter un message
    lcd.print("soit!");
  }
  // Scénario 3
  else if (buttonBuzzerPressed == LOW) {
    // Afficher un message
    lcd.backlight();

    // Changer la position du curseur
    lcd.setCursor(3, 0);

    // Ajouter un message
    lcd.print("Ding");

    // Changer la position du curseur
    lcd.setCursor(3, 1);

    // Ajouter un message
    lcd.print("Dong !");
  }
  // Scénario 1
  else if (motionDetected == HIGH) {
    // Afficher un message
    lcd.backlight();

    // Ajouter un message
    lcd.print("Mouvement");

    // Changer la position du curseur
    lcd.setCursor(0, 1);

    // Ajouter un message
    lcd.print("detecte!");
  }
}

void Handle_Delay() {
  // Vérification if else pour toutes les valeurs

  // Scénario 3
  if (buttonBuzzerPressed == LOW) {
    // Ajouter un délai
    delay(6000);
  }
  // Scénario 1 et 2
  else if (buttonLedPressed == LOW || motionDetected == HIGH) {
    // Ajouter un délai
    delay(4000);

    // Eteindre les deux (même si qu'une seule est allumée)
    digitalWrite(ledButtonPin, LOW);
    digitalWrite(ledMotionPin, LOW);
  }

  // Eteindre l'écran
  lcd.noBacklight();
}

void loop() {
  // Collecte des valeurs
  Get_Values();

  // Utilisation des valeurs
  Update_States();

  // Affichage sur l'écran
  Screen_Output();

  // Ajout d'un delay si besoin
  Handle_Delay();
}