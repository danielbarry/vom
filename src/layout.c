/**
 * layout.c
 *
 * This represents the layout manager for how the system will be laid out onto
 * the display.
 *
 * @author B[]
 **/

/* Includes */
#include <stdlib.h>
#include "display.c"

/* Definitions */
#define TYPE_LEN 255

/* Methods */
void layout_init();
char layout_get_char();

/* Variables */
unsigned int curX;
unsigned int curY;
unsigned int typeLen;
char typeBuffer[TYPE_LEN];

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
  /* Set type length buffer size to zero */
  typeLen = 0;
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
  /* Length of the bag */
  unsigned int len = display_get_width() * display_get_height();
  /* Build a buffer of the right size */
  char* buffer = (char*)malloc(len * sizeof(char));
  /* TODO: Remove these lines. */
  buffer[0] = '{';
  buffer[1] = '"';
  buffer[2] = 'a';
  buffer[3] = '"';
  buffer[4] = ':';
  buffer[5] = '"';
  buffer[6] = 'b';
  buffer[7] = '@';
  buffer[8] = 'c';
  buffer[9] = '.';
  buffer[10] = 'd';
  buffer[11] = '"';
  buffer[12] = '}';
  /* Fill rest of buffer with blanks */
  for(unsigned int x = 13; x < len; x++){
    buffer[x] = ' ';
  }
  /* Run the update in the display */
  display_update(buffer, len);
  /* Free the memory */
  free(buffer);
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
