// PFiller_Init:  Initialization routines which prepare all the periphrials and interrupts for operation


#include "stdbool.h"
#include "PFiller_Globals.h"

// the speed of the feeder (0 is slow to 32 = full speed)
unsigned char _FeederSpeed = 0;

// General status bits concerning overall system operation
unsigned char _FillerStatus = 0x00;

// the index into the weight table that keeps track of weight presets
unsigned char _WeightIndex = 0;

// initialize the target weight that we will try to fill
short _TargetWeight = 0;


//  TODO - Load most recently used settings from EEPROM
void Init_Variables(void) {
}

// the main initialization routine for the filler
// !!! NOTE: ORDER OF INIT DOES MATTER   !!!
void Init_Filler(void) {
    unsigned char i = 0;

    // set up the oscillator
    Init_Oscillator();

    // dummy function for now, this could be an init or state loading function in the future
    Init_Variables();

    // turn off the watch dog timer
    WDTCONbits.SWDTEN = false;

    ANSELA = 0x00;                   // all of port a will be digital
    ANSELB = 0x00;                   // all of port b will be digital
    ANSELC = 0x00;                   // all of port c will be digital

    INTCON2bits.NOT_RBPU = false;    // set the pullups for pins 1, 2, 3, 4 and 5 of port b
    WPUB = 0b00111110;
    TRISBbits.RB4 = INPUT_TRIS;
    TRISBbits.RB5 = INPUT_TRIS;

    // prep the LCD
    Init_LCD();

    // prep the serial comms
    Init_RS232();

    // prep the scale communication pin, interrupts
    Init_Scale();

    // prep the buttons that will be used to interface with the filler
    Init_ButtonInterface();

    // Initialize the DAC
    Init_DAC();

    // splash screen will show for 10 secs
    for (i = 0; i < SPLASHSCREEN_DURATION; i++) {
        Delay_10x_ms(500);
    }

    _InterfaceState = INTERFACE_TYPE_SELECTION;  // start off in item selection mode
    Make_WeightSelectedStr();                    // this should init at the first preset weight
    Redraw_Interface();
    _FillerStatus |= FILLER_CONFIGURING;        // we start off in configuration mode


    // Initialize and nable Interrupts to begin execution of the program
    RCONbits.IPEN = false;              // make sure to turn off interrupt priorities
    INTCON = 0x00;

    // and start the timer interrupt which will be used to poll our muttons
    INTCONbits.TMR0IE = true;
    T0CONbits.TMR0ON = true;

    INTCONbits.PEIE = true;             // Periphreial interrupts on
    INTCONbits.GIE = true;              // Global interrupts on
}


// Configure the oscillator to use the internal oscillator
void Init_Oscillator(void) {
    OSCCON = 0b11110011;               // Idle on sleep (1), Internal Osc 16Mhz (3), - (2), Clock Source Internal (2)
    while (!OSCCONbits.HFIOFS)  { };   //  Wait for internal oscilator to stabilize
}


// Prepare the LCD for use   (No cursor is needed)
void Init_LCD(void) {
    LCD_Initialize(LCD_FUNCTION_FONT_5x8 | LCD_FUNCTION_2_LINES);
    LCD_WaitForNotBusy();
    LCD_WriteCommand(LCD_CMD_DSIPLAY_CNTL | LCD_DISPLAY_ON | LCD_DISPLAY_CURSOR_OFF | LCD_DISPLAY_CURSOR_BLINK_OFF);
    _LCD_Settings = LCD_SETTING_DISPLAY_ON;
    Init_FillerDisplay();
 
}


// Initialize the dac for talking to the feeder controller
void Init_DAC(void)  {
    TRISAbits.RA2 = OUTPUT_TRIS;             // RA2 is our dac so it is an output
    VREFCON2 = _FeederSpeed;                 // this should be zero at initialization
    VREFCON1 = 0b11100000;                   // Enable the DAC to output on DACOUT (RA2) with top voltage of Vdd (5v)s                                             //     low voltage of Vss (0v) and Vss disconnected for
}


//  Initialize the pins for all the buttons that will be used (foot, lcd up/down/select)
void Init_ButtonInterface(void) {

    FOOT_PEDAL_PIN_TRIS = INPUT_TRIS;    // all buttons are set up as inputs
    LCD_UP_BUTTON_TRIS = INPUT_TRIS;
    LCD_DOWN_BUTTON_TRIS = INPUT_TRIS;
    LCD_SELECT_BUTTON_TRIS = INPUT_TRIS;

    // set up timer 0 which will be used to generate interrupts for button debouncing
    T0CON = 0b01010111;             // Timer 0 off (for now), 8-bit, based on instruction clock, falling edge, prescaler on, 1:256 prescaler
    TMR0H = 0x00;
    TMR0L = 99;                     // 156.25 timer ticks should be around 10ms for a processor speed of 16Mhz and 1:256 prescaler
}