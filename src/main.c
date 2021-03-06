/**
 * main.c
 *
 * The main entry point to the program, responsible for handling command line
 * inputs and system logic.
 *
 * @author B[]
 **/

/* Includes */
#include "file.c"
#include "layout.c"
#include <stdio.h>

/* Definitions */
#define VER_MAJ  0
#define VER_MIN  0
#define VER_PAT  3
#define MODE_CMD 1
#define MODE_TYP 2
#define MODE_INS 4

/* Methods */
void main_help();
void main_version();
void main_init();
void main_loop();

/* Constants */
char* MSG_INS = (char*)"-- INSERT --";
char* MSG_ERR = (char*)"Error in command.";
char* MSG_BAD = (char*)"Major error in program.";

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
  /* Forward declare iterators */
  int x;
  int z;
  /* Iterate through the program arguments */
  for(x = 1; x < argc; x++){
    /* Get length of current argument */
    /* NOTE: We can assume that at least one character was collected otherwise
     *       it wouldn't have been added to the list of arguments. */
    int len = sizeof(argv[x]) / sizeof(argv[x][0]);
    /* Test if first character is argument or file */
    if(argv[x][0] == '-'){
      /* Run through the arguments */
      for(z = 0; z < len; z++){
        /* Do task based on parameter */
        switch(argv[x][z]){
          case 'h' :
            /* Display help */
            main_help();
            break;
          case 'v' :
            /* Display version */
            main_version();
            break;
          default :
            /* Handle error */
            layout_set_type_buffer(MSG_ERR);
            break;
        }
      }
    }else{
      /* Initialise the main program */
      main_init();
      /* Initialise the display */
      layout_init();
      /* Load file and display result */
      layout_set_type_buffer(file_open(argv[x]));
      /* Look over character for main program control */
      main_loop();
      /* Force loop exit */
      x = len;
    }
  }
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
  mode = MODE_CMD;
}

/**
 * main_loop()
 *
 * This is the method that runs the main code, with each loop defined by a key
 * press.
 **/
void main_loop(){
  unsigned int x;
  unsigned int tLen;
  char* tBuffer;
  /* Absorb the first key press */
  layout_get_char();
  /* Run forever whilst the program is running */
  while(running){
    /* Update the display */
    layout_update(mode != MODE_INS && mode != MODE_CMD);
    /* Get the next character */
    char chr = layout_get_char();
    /* Operation based on current mode */
    switch(mode){
      case MODE_CMD :
        /* Figure out what is to be done */
        switch(chr){
          case 27 :
            /* Clear output */
            layout_clear_type_buffer();
            break;
          case ':' :
            /* Print the command character */
            layout_update_type(chr);
            /* Go to type mode if colon pressed */
            mode = MODE_TYP;
            break;
          case 'i' :
            /* Set the type buffer to be the mode */
            layout_set_type_buffer(MSG_INS);
            /* Switch to insert mode */
            mode = MODE_INS;
            break;
          default :
            /* Do nothing */
            break;
        }
        break;
      case MODE_TYP :
        /* Figure out what is to be done */
        switch(chr){
          case 10 :
          case 13 :
            /* Get information for the type buffer */
            tLen = layout_get_type_length();
            tBuffer = layout_get_type_buffer();
            /* Is there anything worth processing? */
            if(tLen > 0){
              /* Is it a command we want to run */
              if(tBuffer[0] == ':'){
                /* Iterate through command characters */
                for(x = 1; x < tLen; x++){
                  switch(tBuffer[x]){
                    case 'q' :
                      /* TODO: Check whether we should save. */
                      running = false;
                      /* Clear output */
                      layout_clear_type_buffer();
                      break;
                    default :
                      /* Message an error */
                      layout_set_type_buffer(MSG_ERR);
                      break;
                  }
                }
              }
            }
            break;
          case 27 :
            /* Clear output */
            layout_clear_type_buffer();
            /* Go to back to command mode if escape pressed */
            mode = MODE_CMD;
            break;
          default :
            /* Update the type buffer */
            layout_update_type(chr);
            break;
        }
        break;
      case MODE_INS :
        /* Figure out what is to be done */
        switch(chr){
          case 27 :
            /* Clear output */
            layout_clear_type_buffer();
            /* Go to command mode if escape pressed */
            mode = MODE_CMD;
            break;
          default :
            /* TODO: Requires printing. */
            break;
        }
        break;
      default :
        /* Message an error */
        layout_set_type_buffer(MSG_BAD);
        break;
    }
  }
  /* Close file */
  layout_set_type_buffer(file_close());
  /* Wait for user to read and update display */
  layout_update(mode != MODE_INS && mode != MODE_CMD);
  layout_get_char();
  /* Release the display */
  layout_quit();
}
