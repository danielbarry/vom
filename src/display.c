#include <curses.h>

/* Definitions */
#define COLOUR_NORM  1 /* White */
#define COLOUR_NUMS  2 /* Yellow */
#define COLOUR_MATH  4 /* Maroon */
#define COLOUR_PAIR  8 /* Turquoise */
#define COLOUR_OTHR 16 /* Red */

/* Methods */
void display_init();
void display_update();
char display_get_char();
void display_quit();
void display_update_dimensions();
void display_draw(unsigned int x, unsigned int y, char c);
void display_colourize(char c);

/* Variables */
WINDOW* window;
unsigned int width;
unsigned int height;

void display_init(){
  /* Initialise the display */
  window = initscr();
  /* Turn off wait for enter key */
  cbreak();
  /* Stop echo to the terminal */
  noecho();
  /* Clear the display */
  clear();
}

void display_update(){
  /* Update the display dimensions */
  display_update_dimensions();
  /* TODO: Write this code. */
  display_draw(0, 0, '#'); // TODO: Remove me.
  /* Refresh the display */
  refresh();
}

char display_get_char(){
  /* Returns a character */
  return getch();
}

void display_quit(){
  /* Restore the original window */
  endwin();
}

void display_update_dimensions(){
  /* Update the width and height */
  getmaxyx(window, height, width);
}

void display_draw(unsigned int x, unsigned int y, char c){
  /* Get character to given position */
  move(x, y);
  /* Delete the character currently in the position */
  delch();
  /* Insert a new character into the new position */
  insch(c);
}

/**
 * display_colourize()
 *
 * Colourize the output based on the characters to be displayed.
 *
 * @param c The character being displayed.
 **/
void display_colourize(char c){
  int attribute = COLOUR_NORM;
  if(c >= '0' && c <= '9'){
    attribute = COLOUR_NUMS;
  }
  if(c >= '*' && c <= '/'){
    attribute = COLOUR_MATH;
  }
  if(
    (c >= '(' && c <= ')') ||
    (c >= '[' && c <= ']') ||
    (c >= '{' && c <= '}')
  ){
    attribute = COLOUR_PAIR;
  }
  if(c >= '!' && c <= '&'){
    attribute = COLOUR_OTHR;
  }
  attron(COLOR_PAIR(attribute));
}
