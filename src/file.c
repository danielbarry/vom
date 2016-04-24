/**
 * file.c
 *
 * The handler for a loaded file is responsible for keeping track of a file and
 * making sure that it is handled responsibly. The only requirement is that the
 * disk may be able to handle the addition of the file being worked on.
 *
 * @author B[]
 **/

/* Includes */
#include <stdio.h>

/* Methods */
void file_init();

/* Variables */
bool open;

/**
 * file_init()
 *
 * Initialises the system so that it is ready to handle file operations.
 **/
void file_init(){
  /* Indicate that there is no file open */
  open = false;
}