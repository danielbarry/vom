/**
 * layout.c
 *
 * This represents the layout manager for how the system will be laid out onto
 * the display.
 *
 * @author B[]
 **/

/* Includes */
#include "display.c"

/* Methods */
void layout_init();
char layout_get_char();

/* Variables */
unsigned int curX;
unsigned int curY;

/**
 * layout_init()
 *
 * Initialises the layout manager for the window.
 **/
void layout_init(){
  /* Initialise the display */
  display_init();
  /* Set cursor X and Y to default position */
  curX = 0;
  curY = 0;
}

/**
 * layout_get_char()
 *
 * Get the next character from the keyboard buffer in the terminal.
 *
 * @return The character collected from the keyboard buffer.
 **/
char layout_get_char(){
  /* Returns a character */
  return display_get_char();
}

/**
 * layout_update()
 *
 * Updates the layout.
 **/
void layout_update(){
}

/**
 * layout_quit()
 *
 * Quits the display.
 **/
void layout_quit(){
  /* Run display quit */
  display_quit();
}
