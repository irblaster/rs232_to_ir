# RS232 to IR
Arduino based True RS232 to Infrared Blaster
Based on IRLib2 https://github.com/cyborg5/IRLib2

When power is applied the device will echo the following splash screen:
irblaster.info RS232 IR TX 0.1

Once the splash screen is received, you are ready to send IR codes.

IR Codes are sent with the following command set:
\<IR CODE TYPE\>,\<IR CODE LENGTH\>,\<IR CODE HEX DATA\>

The following values are acceptable for \<IR CODE TPYE\>
-	NEC
-	SONY
-	RC5
-	RC6
-	PANASONIC_OLD
-	JVC
-	NECX
-	SAMSUNG36;
-	GICABLE
-	DIRECTV
-	RCMM
-	CYKM

## Example Codes:

## LG TV 55LE7300
### Power toggle:
NEC,32,0x20DF23DC 
### Power Off:
NEC,32,0x20DFA35C
### Power On:
NEC,32,0x20DF23DC 
### HDMI1:
NEC,32,0x20DF738C 
### HDMI2:
NEC,32,0x20DF33CC 
### HDMI3:
NEC,32,0x20DF9768 
### HDMI4:
NEC,32,0x20DF5BA4 
### Volume Up:
NEC,32,0x20DF40BF 
### Volume Down:
NEC,32,0x20DFC03F 

## Vizio TV D55x-G1

### Power Toggle:
NEC,32,0x20DF10EF
### Power Off:
NEC,32,0x20DFA45B 
### Power On:
NEC,32,0x20DF54AB 
### HDMI 1:
NEC,32,0x20DF817E 
### HDMI 2:
NEC,32,0x20DF41BE 
### HDMI 3:
NEC,32,0x20DFC13E 
### HDMI 4:
NEC,32,0x20DF21DE 
### Volume Up:
NEC,32,0x20DF40BF 
### Volume Down:
NEC,32,0x20DFC03F

The device will echo back “IR Sent” when a valid command was received.

The device can also accept raw codes in the format:

RAW,<Number of Mark/Space Values>,<Mark/Space Values>

Example raw code transmission:
## Panasonic TV:
### Power On:
RAW,100,3514, 1718, 458, 422, 458, 1306, 430, 450, 430, 422, 458, 422, 458, 426, 454, 426, 430, 450, 430, 450, 430, 450, 430, 426, 458, 422, 458, 422, 458, 1306, 426, 426, 458, 422, 458, 422, 458, 422, 458, 422, 430, 454, 430, 450, 430, 422, 458, 422, 458, 1306, 430, 450, 430, 450, 430, 422, 458, 426, 454, 426, 458, 422, 430, 450, 430, 450, 430, 454, 430, 1306, 426, 1306, 454, 1306, 430, 1306, 454, 1306, 430, 450, 430, 450, 430, 450, 430, 1306, 430, 1334, 426, 1306, 430, 1302, 458, 1306, 430, 450, 430, 1302, 458, 1000

