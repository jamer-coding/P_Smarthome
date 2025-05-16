#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);           // Ajout de l'écran LCD (situé à l'adresse 0x27 écran de 16 caractères et 2 lignes) comme référence dans le code

const int PIN_MotionDetector = 9;           // Le pin du détecteur de mouvement
const int PIN_LED_MotionDetector = 4;       // Le pin de la lampe LED

const int PIN_Button_LED = 7;               // Le pin du bouton relié à une LED
const int PIN_LED_Button = 2;               // Le pin de la lampe LED relié à un bouton

const int PIN_Button_Buzzer = 10;           // Le pin du bouton relié au buzzer
const int PIN_Buzzer = 8;                   // Le pin du buzzer relié au bouton

int VAL_Button_LED = HIGH;                  // Variable utilisé pour un détecteur de mouvement
int VAL_MotionDetector = LOW;               // Variable utilisé pour un bouton qui controle une LED
int VAL_Button_Buzzer = HIGH;               // Variable utilisé pour un bouton qui controle un buzzer 

void setup() {
  // Initialisation de l'écran LCD
  lcd.init();

  // Setup scénario 1
  pinMode(PIN_MotionDetector, INPUT);
  pinMode(PIN_LED_MotionDetector, OUTPUT);

  // Setup scénario 2
  pinMode(PIN_Button_LED, INPUT);
  pinMode(PIN_LED_Button, OUTPUT);

  // Setup scénario 3
  pinMode(PIN_Button_Buzzer, INPUT);
  pinMode(PIN_Buzzer, OUTPUT);
}


void Get_Values() {
  // Lecture du signal du détecteur de mouvement
  VAL_MotionDetector = digitalRead(PIN_MotionDetector);

  // Lecture du signal du bouton qui controle une LED
  VAL_Button_LED = digitalRead(PIN_Button_LED);

  // Lecture du signal du bouton qui controle un buzzer
  VAL_Button_Buzzer = digitalRead(PIN_Button_Buzzer);
}

void Update_States() {
  // Vérification if pour toutes les valeurs

  // Scénario 1
  if (VAL_MotionDetector == HIGH) {
    // Allumer la LED
    digitalWrite(PIN_LED_MotionDetector, HIGH);
  }
  // Scénario 2
  if (VAL_Button_LED == LOW) {
    // Allumer la LED
    digitalWrite(PIN_LED_Button, HIGH);
  }
  // Scénario 3
  if (VAL_Button_Buzzer == LOW) {
    // Activer le buzzer (pin, fréquence en Hz, durée en ms)
    tone(PIN_Buzzer, 200, 1000);
  }
}

void Screen_Output() {
  // Effacer l'écran
  lcd.clear();

  // Vérification if else pour toutes les valeurs

  // Scénario 2
  if (VAL_Button_LED == LOW) {
    // Afficher un message
    lcd.backlight();

    // Ajouter un message
    lcd.print("Que la lumiere");

    // Changer la position du curseur
    lcd.setCursor(0, 1);

    // Ajouter un message
    lcd.print("soit !");
  }
  // Scénario 3
  else if (VAL_Button_Buzzer == LOW) {
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
  else if (VAL_MotionDetector == HIGH) {
    // Afficher un message
    lcd.backlight();

    // Ajouter un message
    lcd.print("Mouvement");

    // Changer la position du curseur
    lcd.setCursor(0, 1);

    // Ajouter un message
    lcd.print("detecte !");
  }
}

void Handle_Delay() {
  // Vérification if else pour toutes les valeurs

  // Scénario 3
  if (VAL_Button_Buzzer == LOW) {
    // Ajouter un délai
    delay(1500);
  }
  // Scénario 1 et 2
  else if (VAL_Button_LED == LOW || VAL_MotionDetector == HIGH) {
    // Ajouter un délai
    delay(4000);

    // Eteindre les deux (même si qu'une seule est allumée)
    digitalWrite(PIN_LED_Button, LOW);
    digitalWrite(PIN_LED_MotionDetector, LOW);
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