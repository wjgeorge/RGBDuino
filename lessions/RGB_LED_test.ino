#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int n;

#define PIN1 13
#define PIN2 12

#define LED1 8
#define LED2 9;
#define LED3 10;
#define LED4 11;
#define LED7 2 ;
#define LED8 3 ;
#define LED9 4;
#define LED10 5;
#define LED11 6;
#define LED12 7;

#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
// List the frequencies of all D keys
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
// List all beats
int tune[]= // List each frequency according to the numbered musical notation
{
	NTD3, NTD3, NTD4, NTD5,
	NTD5, NTD4, NTD3, NTD2,
	NTD1, NTD1, NTD2, NTD3,
	NTD3, NTD2, NTD2,
	NTD3, NTD3, NTD4, NTD5,
	NTD5, NTD4, NTD3, NTD2,
	NTD1, NTD1, NTD2, NTD3,
	NTD2,NTD1,NTD1,
	NTD2, NTD2, NTD3, NTD1,
	NTD2, NTD3, NTD4, NTD3, NTD1,
	NTD2, NTD3, NTD4, NTD3, NTD2,
	NTD1, NTD2, NTDL5, NTD0,
	NTD3, NTD3, NTD4, NTD5,
	NTD5, NTD4, NTD3, NTD4, NTD2,
	NTD1, NTD1, NTD2, NTD3,
	NTD2,NTD1,NTD1
};
float durt[]= // List the beats according to the numbered musical notation
{
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	1+0.5,0.5,1+1,
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	1+0.5,0.5,1+1,
	1,1,1,1,
	1,0.5,0.5,1,1,
	1,0.5,0.5,1,1,
	1,1,1,1,
	1,1,1,1,
	1,1,1,0.5,0.5,
	1,1,1,1,
	1+0.5,0.5,1+1,
};
int length;
#define tonepin 8 //Use port 6
// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number(most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream(most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz(classic 'v1'(not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream(most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream(v1 FLORA pixels, not v2)
// NEO_RGBW Pixels are wired for RGBW bitstream(NeoPixel RGBW products)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(1, PIN2, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel. Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined(__AVR_ATtiny85__)
	if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
	// End of trinket special code
	for(n=2;n<=13;n++)
	{
		pinMode(n, OUTPUT); 
	}

	strip1. begin();
	strip2. begin();
	strip1.show(); // Initialize all pixels to 'off'
	strip2.show();

	pinMode(tonepin,OUTPUT);
	length = sizeof(tune)/ sizeof(tune[ 0 ]); // Calculate the length
}

void loop() {
	// Some example procedures showing how to display to the pixels:
	colorWipe(strip1.Color(50, 0, 0), 100); // Red
	colorWipe(strip2.Color(255, 0, 0), 100); // Red
	colorWipe(strip1.Color(0, 50, 0), 100); // Green
	colorWipe(strip2.Color(0, 255, 0), 100); // Green
	colorWipe(strip1.Color(0, 0, 50), 100); // Blue
	colorWipe(strip2.Color(0, 0, 255), 100); // Blue
	turn1(); // Sequentially lit, sequence extinguished
	clean(); // Turn off all lights
	// turn2();//6 lights flash
	// clean();//Turn off all lights
	// turn3();
	// clean();//Turn off all lights
	for(int x=0;x<length;x++)
	{
		tone(tonepin,tune[x]);
		delay( 200 *durt[x]); // This is used to adjust the delay according to the beat. The index of 500 can be adjusted by yourself. In this music, I found that 500 is more appropriate.
		noTone(tonepin);
	}
	delay(2000);

}
// Fill the dots one after the other with a color


void colorWipe(uint32_t c, uint8_t wait) {
	for(uint16_t i=0; i<strip1.numPixels(); i++) {
		strip1.setPixelColor(i, c);
		strip1.show();
		delay(wait);
	}
	for(uint16_t i=0; i<strip2.numPixels(); i++) {
		strip2.setPixelColor(i, c);
		strip2.show();
		delay(wait);
	}
}
void  turn1() // Sequentially lights up and turns off sequentially
{
	for(n=2;n<=13;n++)
	{
		digitalWrite(n,HIGH);
		delay(300);
	}
	for(n=2;n<=13;n++)
	{
		digitalWrite(n,LOW);
		delay(300);
	}
}
void  turn2() // 6 lights flash 3 times
{
	for(int x=0;x<=2;x++)
	{
		for(n=2;n<=13;n++)
		{
			digitalWrite(n,HIGH); 
		}
		delay(300); 
		for(n=2;n<=13;n++)
		{
			digitalWrite(n,LOW); 
		}
		delay(300);
	}
}
void  turn3() // Two two flash together 3 times
{
	for(int x=0;x<=2;x++)
	{
		digitalWrite(8,HIGH);
		digitalWrite(9,HIGH);
		for(n=10;n<=11;n++){
			digitalWrite(n,LOW);
		}
		delay(300);
		digitalWrite(10,HIGH);
		digitalWrite(11,HIGH);
		digitalWrite(8,LOW);
		digitalWrite(9,LOW);
		delay(300);
		for(n=2;n<=11;n++){
			digitalWrite(n,LOW);
		}
		delay(300);
	}
}
void clean()
{
	for(n=2;n<=11;n++)
	{
		digitalWrite(n,LOW); 
	}
	delay(300);
}
