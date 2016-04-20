#include "display.c"

/* Definitions */
#define MODE_CMD 1
#define MODE_TYP 2
#define MODE_INS 4

/* Methods */
void main_init();
void main_loop();

/* Variables */
bool running;

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

void main_init(){
  running = true;
}

void main_loop(){
  /* Initialise the display */
  display_init();
  /* TODO: Write this code. */
  while(running){
    display_update();
    char chr = display_get_char();
    if(chr == 'q'){
      running = false;
    }
  }
  /* Release the display */
  display_quit();
}
