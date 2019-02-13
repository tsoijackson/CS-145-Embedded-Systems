/*
 * Project 3.c
 *
 * Created: 1/30/2019 12:26:36 PM
 * Author : Jackson Tsoi
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "avr.h"
#include "lcd.h"

struct Note  {
	double frequency;
	double duration;
};

#define TOTAL_NOTES 12
struct Note NOTES[TOTAL_NOTES] = {};

char keypad[17] = {
	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
	'*', '0', '#', 'D'
};

int is_pressed(int row, int col) {
	DDRC = 0;
	PORTC = 0;
	
	SET_BIT(DDRC, row);
	SET_BIT(PORTC, col + 4);
	avr_wait(1);
	
	if (GET_BIT(PINC,col + 4)) {
		return 0;
	}
	
	return 1;
}

int get_key() {
	int row, col;
	for (row = 0; row < 4; ++row) {
		for (col = 0; col < 4; ++col) {
			if (is_pressed(row,col)) {
				return (row * 4) + col + 1;
			}
		}
	}
	return 0;
}

void blinkNtimes(int times) {
	for(int i = 0; i < times; ++i) {
		blink();
	}
}

void blink() {
	SET_BIT(PORTB,0);
	avr_wait(500);
	CLR_BIT(PORTB,0);
	avr_wait(500);
}

void play_song() {
	
}

void play_note(int frequency,int duration) {
	int TH = (1 / frequency) / 2;
	int TL;
	for (int i = 0; i < duration; ++i) {
		SET_BIT(PORTA,0);
		avr_wait(1);
		CLR_BIT(PORTA,0);
		avr_wait(1);
	}
}

void notes_init() {
	int frequency = 220;
	for (int i = 0; i < TOTAL_NOTES; ++i){
		NOTES[i].frequency = pow(2.0, (double)i / TOTAL_NOTES ) * frequency;
		NOTES[i].duration = 5; //(1/NOTES[i].frequency) / 2
	}
}

int main(void)
{
	avr_init();
	lcd_init();
	notes_init();
	DDRA = 0x01;
    while (1) 
    {
		int key = get_key() - 1;
		if (key == -1) {
			// Do Nothing
		}
		else if (keypad[key] == '1')
		{
			play_note(NOTES[0].frequency, NOTES[0].duration);
		}
		avr_wait(1);
    }
}
