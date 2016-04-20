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

/**
 * display_init()
 *
 * Initialise the display.
 **/
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

/**
 * display_update()
 *
 * Update the display.
 **/
void display_update(){
  /* Update the display dimensions */
  display_update_dimensions();
  /* TODO: Write this code. */
  display_draw(0, 0, '#'); // TODO: Remove me.
  /* Refresh the display */
  refresh();
}

/**
 * display_get_char()
 *
 * Get the next character from the keyboard buffer in the terminal.
 *
 * @return The character collected from the keyboard buffer.
 **/
char display_get_char(){
  /* Returns a character */
  return getch();
}

/**
 * display_quit()
 *
 * Releases the display to the next program.
 **/
void display_quit(){
  /* Restore the original window */
  endwin();
}

/**
 * display_update_dimensions()
 *
 * Updates the dimensions of the display to be used to determine feature
 * positions.
 **/
void display_update_dimensions(){
  /* Update the width and height */
  getmaxyx(window, height, width);
}

/**
 * display_draw()
 *
 * Draws a character at a given position with a given attribute.
 *
 * @param x The X position to draw at.
 * @param y The Y position to draw at.
 * @param c The character to be draw at the given position.
 **/
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
