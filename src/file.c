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
char* file_close();
void file_set_pos(long int pos);
char file_read();

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

/**
 * file_close()
 *
 * Closes a file if it is open.
 **/
char* file_close(){
  /* Make sure the file is open */
  if(open){
    /* Make sure the file pointer is not NULL */
    if(file != NULL){
      /* Close the file */
      int res = fclose(file);
      /* Figure out whether the operation was successful */
      if(res == 0){
        return FILE_MSG_OK;
      }
    }
  }
  /* By default, return bad */
  return FILE_MSG_BAD;
}

/**
 * file_set_pos()
 *
 * Set the position in the file to set the read/write position to. No error is
 * given by this function as it is the responsibility of the caller not to
 * overrun the file in either direction.
 *
 * @param pos The position in the file.
 **/
void file_set_pos(long int pos){
  /* Set the position relative to the beginning of the file */
  fseek(file, pos, SEEK_SET);
}

/**
 * file_read()
 *
 * Reads a character from the file stream, returning an EOF if the end of the
 * file is reached.
 *
 * @return The character that has been read.
 **/
char file_read(){
  /* Get the next character from the file */
  return (char)fgetc(file);
}
