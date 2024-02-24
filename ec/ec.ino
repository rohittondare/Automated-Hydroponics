int ecVal;
float voltage;
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
ecVal = analogRead(A0);
voltage = ecVal * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
  delay(1000);
  c_readPpm();
}

/* zeroppm command 
int c_zeroPpm(int  argc,char **args) {
  m_cfg.ppmoset=readADC(ADC_CH0); //Read ADC channel 0, store as offset
  meterSave(m_cfg); //Save settings to eeprom
  return(m_cfg.ppmoset);
}
*/


 
/* scaleppm command, if argument calibrates to ARG1 ppm, otherwise defaults to 1000 
int c_scalePpm(int  argc,char **args) {
  if(argc==1) {
    printf("usage: calibppm PPM\r\n");
    return(ERROR);
  }
  if(argc==0) { // calcuate scale using CALIBPPM/(ADC-offset)
    m_cfg.ppmscale=((long)(((long)100000)/(readADC(ADC_CH0)-m_cfg.ppmoset)));
  }
  if(argc==2) { //same but with arg1 as calib, note the *100 for fixed point
    m_cfg.ppmscale=((long)(((long)numtoint(args[1])*100)/(readADC(ADC_CH0)-m_cfg.ppmoset)));
  } 
  meterSave(m_cfg); //Save settings to eeprom
  return(m_cfg.ppmscale);
}
*/
 
/* readppm */
int c_readPpm() {
  long ppm;
  long ppmoset=1;
long ppmscale=((long)(((long)100000)/(voltage)));
  ppm=((long)(voltage)-ppmoset)*ppmscale/100;
  //display the results
  Serial.print(ppm);
  
}
