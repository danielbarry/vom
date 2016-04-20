#include "display.c"

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
  main_init();
  main_loop();
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
        /* TODO: Write this code. */
        break;
      case MODE_TYP :
        /* TODO: Write this code. */
        break;
      case MODE_INS :
        /* TODO: Write this code. */
        break;
      default :
        /* TODO: Handle error in some way. */
        break;
    }
  }
  /* Release the display */
  display_quit();
}
