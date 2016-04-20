/* Includes */
#include "display.c"
#include <stdio.h>

/* Definitions */
#define VER_MAJ  0
#define VER_MIN  0
#define VER_PAT  1
#define MODE_CMD 1
#define MODE_TYP 2
#define MODE_INS 4

/* Methods */
void main_help();
void main_version();
void main_init();
void main_loop();

/* Variables */
bool running;
unsigned int mode;

/**
 * main()
 *
 * The main entry method into the program.
 *
 * @param argc The number of arguments parsed to the program.
 * @param argv The parameters that were passed to the program.
 **/
int main(int argc, char** argv){
  /* Iterate through the program arguments */
  for(int x = 1; x < argc; x++){
    /* Get length of current argument */
    /* NOTE: We can assume that at least one character was collected otherwise
     *       it wouldn't have been added to the list of arguments. */
    int len = sizeof(argv[x]) / sizeof(argv[x][0]);
    /* Test if first character is argument or file */
    if(argv[x][0] == '-'){
      /* Run through the arguments */
      for(int z = 0; z < len; z++){
        /* Do task based on parameter */
        switch(argv[x][z]){
          case 'h' :
            /* Display help */
            main_help();
            break;
          case 'v' :
            /* Display version */
            main_version();
            break;
          default :
            /* TODO: Handle error. */
            break;
        }
      }
    }else{
      /* Initialise the main program */
      main_init();
      /* Look over character for main program control */
      main_loop();
      /* TODO: Load file. */
      /* Force loop exit */
      x = len;
    }
  }
}

/**
 * main_help()
 *
 * Display help for this program to the terminal over the standard output.
 **/
void main_help(){
  printf("\nvom [OPT] [FILE]");
  printf("\n");
  printf("\n  OPTions");
  printf("\n");
  printf("\n    -h    Displays the help.");
  printf("\n    -v    Displays the version.");
  printf("\n");
  printf("\n  FILE");
  printf("\n");
  printf("\n    A file to be loaded form disk.");
  printf("\n");
}

/**
 * main_version()
 *
 * Display the version of this program to the terminal over the standard
 * output.
 **/
void main_version(){
  printf("\nver %i.%i.%i\n", VER_MAJ, VER_MIN, VER_PAT);
}

/**
 * main_init()
 *
 * Initialise the main code.
 **/
void main_init(){
  running = true;
}

/**
 * main_loop()
 *
 * This is the method that runs the main code, with each loop defined by a key
 * press.
 **/
void main_loop(){
  /* Initialise the display */
  display_init();
  /* TODO: Write this code. */
  while(running){
    /* Update the display */
    display_update();
    /* Get the next character */
    char chr = display_get_char();
    /* Operation based on current mode */
    switch(mode){
      case MODE_CMD :
        /* Figure out what is to be done */
        switch(chr){
          case 27 :
            /* Go to type mode if escape pressed */
            mode = MODE_TYP;
            break;
          case 'i' :
            /* Switch to insert mode */
            mode = MODE_INS;
            break;
          default :
            /* Do nothing */
            break;
        }
        break;
      case MODE_TYP :
        /* Figure out what is to be done */
        switch(chr){
          case 27 :
            /* Go to back to command mode if escape pressed */
            mode = MODE_CMD;
            break;
          default :
            /* TODO: Requires printing. */
            break;
        }
        break;
        break;
      case MODE_INS :
        /* Figure out what is to be done */
        switch(chr){
          case 27 :
            /* Go to command mode if escape pressed */
            mode = MODE_CMD;
            break;
          default :
            /* TODO: Requires printing. */
            break;
        }
        break;
      default :
        /* TODO: Handle error in some way. */
        break;
    }
  }
  /* Release the display */
  display_quit();
}
