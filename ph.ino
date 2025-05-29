const int analogInPin = A0; 
int buf[10];
int temp=0;
unsigned long int inValue; 
void setup() {
 // usaremos el puerto serial para enviar los datos
  Serial.begin(9600); 
  
}

void loop() {
  /*para evitar demasiadas variaciones lecturaremos 
   unos varios valores y luego sacaremos el promedio*/
   for(int i=0; i<10;i++){
    /*realizamos 10 lecturasy almacenamos en buff*/
      buf[i]= analogRead(analogInPin);
      delay(10);
   }
   /*luego realizamos un barrido de los valores lecturados
    * y descartamos los valores demasiado elevados y los 
    * valoresdemasiado vajos*/
    for(int i=0; i<9; i++){
      for(int j=i+1;j<10;j++){
        temp= buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }  
    }
    /*realicamos el calculo del promedio y la conversion
    a voltaje en mv*/
    inValue=0;
    for(int i=2; i<8; i++){
        inValue= inValue + buf[i];
    }
    float PHVol= (float)inValue*100*5/1024/6;
   
    
    Serial.print("Voltaje mv =");
    Serial.println(PHVol);

     /*agregamos la ecuacion encontrada*/
    float PH= -0.0602*PHVol+21.8;
    Serial.print("PH =");
    Serial.println(PH);
    delay(100);
}