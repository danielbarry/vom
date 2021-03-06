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
void layout_update(bool mode);
void layout_update_type(char c);
char* layout_get_type_buffer();
unsigned int layout_get_type_length();
void layout_set_type_buffer(char* chrs);
void layout_clear_type_buffer();

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
 *
 * @param mode The cursor mode for the text editor update, false for window and
 * true for command.
 **/
void layout_update(bool mode){
  unsigned int x;
  /* Length of the bag */
  unsigned int width = display_get_width();
  unsigned int height = display_get_height();
  unsigned int len = width * height;
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
  for(x = 13; x < len; x++){
    buffer[x] = ' ';
  }
  /* Update last line with last width characters in type buffer */
  int p = 0;
  for(x = typeLen > width ? typeLen - width : 0; x < typeLen; x++){
    /* Update the character in the buffer with the new data */
    buffer[(width * (height - 1)) + p] = typeBuffer[x];
    /* Update type position for display */
    p++;
  }
  /* Run the update in the display */
  display_update(buffer, len);
  /* Work out if we are in typing mode */
  if(mode){
    display_set_position(height - 1, typeLen);
  }else{
    display_set_position(curX, curY);
  }
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

/**
 * layout_update_type()
 *
 * Update the type buffer to reflect the addition of a character destined for
 * the buffer.
 *
 * @param c The character to be considered.
 **/
void layout_update_type(char c){
  /* Check if the character is deleted */
  if(c == 8 || c == 127){
    /* Make sure buffer is not already at the beginning */
    if(typeLen > 0){
      typeLen--;
    }
  }else{
    /* Check if we won't exceed our buffer */
    if(typeLen < TYPE_LEN){
      /* Update the type buffer */
      typeBuffer[typeLen] = c;
      typeLen++;
    }
  }
}

/**
 * layout_get_type_buffer()
 *
 * Gets the characters from the type buffer.
 *
 * @return The character buffer of the type buffer.
 **/
char* layout_get_type_buffer(){
  return typeBuffer;
}

/**
 * layout_get_type_length()
 *
 * Gets the length of the type buffer.
 *
 * @return The length of the type buffer.
 **/
unsigned int layout_get_type_length(){
  return typeLen;
}

/**
 * layout_set_type_buffer()
 *
 * Sets the data in characters in the type buffer.
 *
 * @param chrs The characters to set the buffer too.
 **/
void layout_set_type_buffer(char* chrs){
  unsigned int x;
  /* Set initial buffer size to zero */
  typeLen = 0;
  /* Iterate until we reach the end of the string or maximum */
  for(x = 0; x < TYPE_LEN; x++){
    /* Check if the end has been reached */
    if(chrs[x] != '\0'){
      /* Add character to the buffer */
      typeBuffer[x] = chrs[x];
      /* Increment size */
      typeLen++;
    }else{
      /* Stop processing */
      break;
    }
  }
}

/**
 * layout_clear_type_buffer()
 *
 * Clear the buffer of the type buffer by setting the collection down to zero.
 **/
void layout_clear_type_buffer(){
  /* Set collection point back down to zero */
  typeLen = 0;
}
