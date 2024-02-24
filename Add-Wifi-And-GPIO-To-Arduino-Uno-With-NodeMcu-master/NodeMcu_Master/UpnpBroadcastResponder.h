const int analogPinA0 = A0;
const int analogPinA1 = A1;
const int analogPinA2 = A2;
const int analogPinA3 = A3;

void setup() {
  Serial.begin(9600);
   // Define the conditions and ranges for each pin

}

void loop() {
  int valueA0 = analogRead(analogPinA0);
  int valueA1 = analogRead(analogPinA1);
  int valueA2 = analogRead(analogPinA2);
  int valueA3 = analogRead(analogPinA3);
  
  int thresholdSW1 = 768;
  int thresholdSW2 = 683;
  int thresholdSW3 = 450;
  int thresholdSW4 = 589;
  int thresholdSW5 = 549;
  int thresholdSW6 = 450;
  int thresholdSW7 = 589;
  int thresholdSW8 = 549;
  int thresholdSW9 = 768;
  int thresholdSW10 = 683;
  int thresholdSW1_2 = 559;
  int thresholdSW3_4 = 437;
  int thresholdSW3_5 = 326;
  int thresholdSW4_5 = 512;
  int thresholdSW3_4_5 = 288;
  int thresholdSW6_7 = 437;
  int thresholdSW7_8 = 512;
  int thresholdSW6_8 = 326;
  int thresholdSW6_7_8= 288;
  int thresholdSW9_10 = 559;
  int threshold5V = 1023; 
  int range = 5;

  bool switchFlags[] = {false, false, false, false, false, false, false, false, false, false};
  if (valueA0 > threshold5V - range && valueA1 > threshold5V - range && valueA2 > threshold5V - range && valueA3 > threshold5V - range){
      Serial.println("No Switch is Pressed");
   }
   else if ((valueA0 > thresholdSW1_2 - range && valueA0 < thresholdSW1_2 + range) && (valueA1 > thresholdSW3_4_5 - range && valueA1 < thresholdSW3_4_5 + range) && (valueA2 > thresholdSW6_7_8 - range && valueA2 < thresholdSW6_7_8 + range) && (valueA3 > thresholdSW9_10 - range && valueA3 < thresholdSW9_10 + range)) {
      Serial.println("All Switches are Pressed");
   }
   else {
	//Serial.println(valueA0);
	if (valueA0 > thresholdSW1 - range && valueA0 < thresholdSW1 + range) {
	  Serial.println("Switch1 is pressed");
	  switchFlags[0] = true;
	}
	else if (valueA0 > thresholdSW2 - range && valueA0 < thresholdSW2 + range) {
	 Serial.println("Switch2 is pressed");
	 switchFlags[1] = true;
	}
	else if (valueA0 > thresholdSW1_2 - range && valueA0 < thresholdSW1_2 + range) {
	 Serial.println("Switch1 and Switch2 are pressed");
	 switchFlags[0] = true;
	 switchFlags[1] = true;
	}
	
	
	// Check Values on Pin A1
	if (valueA1 > thresholdSW3 - range && valueA1 < thresholdSW3 + range) {
	  Serial.println("Switch3 is pressed");
	  switchFlags[2] = true;
	}
	else if (valueA1 > thresholdSW4 - range && valueA1 < thresholdSW4 + range) {
	  Serial.println("Switch4 is pressed");
	  switchFlags[3] = true;
	}
	else if (valueA1 > thresholdSW5 - range && valueA1 < thresholdSW5 + range) {
	  Serial.println("Switch5 is pressed");
	  switchFlags[4] = true;
	}
	else if (valueA1 > thresholdSW3_4 - range && valueA1 < thresholdSW3_4 + range) {
	  Serial.println("Switch3 and Switch4 are pressed");
	  switchFlags[2] = true;
	  switchFlags[3] = true;
	}
	else if (valueA1 > thresholdSW4_5 - range && valueA1 < thresholdSW4_5 + range) {
	  Serial.println("Switch4 and Switch5 are pressed");
	  switchFlags[3] = true;
	  switchFlags[4] = true;
	}
	else if (valueA1 > thresholdSW3_5 - range && valueA1 < thresholdSW3_5 + range) {
	  Serial.println("Switch3 and Switch5 are pressed");
	  switchFlags[2] = true;
	  switchFlags[4] = true;
	}
	else if (valueA1 > thresholdSW3_4_5 - range && valueA1 < thresholdSW3_4_5 + range) {
	  Serial.println("Switch3, Switch4, and Switch5 are pressed");
	  switchFlags[2] = true;
	  switchFlags[3] = true;
	  switchFlags[4] = true;
	}
	
	// Check Values on Pin A2
	 if (valueA2 > thresholdSW6 - range && valueA2 < thresholdSW6 + range) {
	   Serial.println("Switch6 is pressed");
	   switchFlags[5] = true;
	 }
	 else if (valueA2 > thresholdSW7 - range && valueA2 < thresholdSW7 + range) {
	   Serial.println("Switch7 is pressed");
	   switchFlags[6] = true;
	 }
	 else if (valueA2 > thresholdSW8 - range && valueA2 < thresholdSW8 + range) {
	   Serial.println("Switch8 is pressed");
	   switchFlags[7] = true;
	 }
	 else if (valueA2 > thresholdSW6_7 - range && valueA2 < thresholdSW6_7 + range) {
	   Serial.println("Switch6 and Switch7 are pressed");
	   switchFlags[5] = true;
	   switchFlags[6] = true;
	 }
	 else if (valueA2 > thresholdSW7_8 - range && valueA2 < thresholdSW7_8 + range) {
	   Serial.println("Switch7 and Switch8 are pressed");
	   switchFlags[6] = true;
	   switchFlags[7] = true;
	 }
	 else if (valueA2 > thresholdSW6_8 - range && valueA2 < thresholdSW6_8 + range) {
	   Serial.println("Switch6 and Switch8 are pressed");
	   switchFlags[5] = true;
	   switchFlags[7] = true;
	 }
	 else if (valueA2 > thresholdSW6_7_8 - range && valueA2 < thresholdSW6_7_8 + range) {
	   Serial.println("Switch6, Switch7, and Switch8 are pressed");
	   switchFlags[5] = true;
	   switchFlags[6] = true;
	   switchFlags[7] = true;
	 }

	 // Check Values on Pin A3
	 if (valueA3 > thresholdSW9 - range && valueA3 < thresholdSW9 + range) {
	   Serial.println("Switch9 is pressed");
	   switchFlags[8] = true;
	 }
	 else if (valueA3 > thresholdSW10 - range && valueA3 < thresholdSW10 + range) {
	   Serial.println("Switch10 is pressed");
	   switchFlags[9] = true;
	 }
	 else if (valueA3 > thresholdSW9_10 - range && valueA3 < thresholdSW9_10 + range) {
	   Serial.println("Switch9 and Switch10 are pressed");
	   switchFlags[8] = true;
	   switchFlags[9] = true;
	 }

	 // Print all pressed switches
	 Serial.println("Switch Pressed:");
	 for (int i = 0; i < sizeof(switchFlags) / sizeof(switchFlags[0]); i++) {
	   if (switchFlags[i]) {
	     Serial.print(i + 1);
	     Serial.print(" ");
	   }
	 }
	 Serial.println();

	/* Check Values on Pin A2
	if (valueA2 > thresholdSW6 - range && valueA2 < thresholdSW6 + range) {
	  Serial.println("Switch6 is pressed");
	}
	else if (valueA2 > thresholdSW7 - range && valueA2 < thresholdSW7 + range) {
	  Serial.println("Switch7 is pressed");
	}
	else if (valueA2 > thresholdSW8 - range && valueA2 < thresholdSW8 + range) {
	  Serial.println("Switch8 is pressed");
	}
	else if (valueA2 > thresholdSW6_7 - range && valueA2 < thresholdSW6_7 + range) {
	  Serial.println("Switch6 and Switch7 are pressed");
	}
	else if (valueA2 > thresholdSW7_8 - range && valueA2 < thresholdSW7_8 + range) {
	  Serial.println("Switch7 and Switch8 are pressed");
	}
	else if (valueA2 > thresholdSW6_8 - range && valueA2 < thresholdSW6_8 + range) {
	  Serial.println("Switch6 and Switch8 are pressed");
	}
	else if (valueA2 > thresholdSW6_7_8 - range && valueA2 < thresholdSW6_7_8 + range) {
	  Serial.println("Switch6, Switch7, and Switch8 are pressed");
	}
	
	// Check Values on Pin A3
	if (valueA3 > thresholdSW9 - range && valueA3 < thresholdSW9 + range) {
	  Serial.println("Switch9 is pressed");
	}
	else if (valueA3 > thresholdSW10 - range && valueA3 < thresholdSW10 + range) {
	 Serial.println("Switch10 is pressed");
	}
	else if (valueA3 > thresholdSW9_10 - range && valueA3 < thresholdSW9_10 + range) {
	 Serial.println("Switch9 and Switch10 are pressed");
	}*/
    }

  delay(1000);  
}
