const int button = 2;
const int led = 10;

int pin_state = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
pinMode(button,INPUT);
}

void loop() {
pin_state = digitalRead(button);
if(pin_state==HIGH){
  digitalWrite(led,HIGH); //light on
}
else{
  digitalWrite(led,LOW); //led off
}
}
