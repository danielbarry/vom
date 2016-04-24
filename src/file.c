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
#include <stdbool.h>
#include <stdio.h>

/* Methods */
void file_init();
char* file_open(char* filename);

/* Constants */
const char* FILE_ATT = (char*)"r+b";
char* FILE_MSG_OK = (char*)"File operation success.";
char* FILE_MSG_BAD = (char*)"Failed file I/O.";

/* Variables */
FILE* file;
bool open;

/**
 * file_init()
 *
 * Initialises the system so that it is ready to handle file operations.
 **/
void file_init(){
  /* Set the file pointer to NULL */
  file = NULL;
  /* Indicate that there is no file open */
  open = false;
}

/**
 * file_open()
 *
 * Opens a file for reading and writing.
 *
 * @param filename The path of the file.
 **/
char* file_open(char* filename){
  /* Open the file for binary read and write */
  file = fopen(filename, FILE_ATT);
  /* Work out how successful the file open was */
  if(file != NULL){
    /* Set the file to be open */
    open = true;
    /* Return a good message */
    return FILE_MSG_OK;
  }else{
    /* Return a bad message */
    return FILE_MSG_BAD;
  }
}
