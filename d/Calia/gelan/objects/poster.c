/* 	this is a poster for the guards info office in Gelan
 
    coder(s):   Deinonychus

    history:
		14.02.94	reading description from file	Deinonychus
		26.02.93	created				Deinonychus

    purpose:    poster

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "object.h"
#include <stdproperties.h>

create_object()
{
    /* descriptions */

    set_name("poster");
    set_short("poster");
    set_pshort("posters");
    set_long("You wonder what this poster's good for.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 5);
} /* create_object */


/*
 * Function name: read_long
 * Description:   reads the long description from a given file
 * Arguments:     filename holding the description
 * Returns:       none
 */
void
read_long(string filename)
{
  string long;

  long = read_file(filename);

  if(strlen(long) > 0){
    set_long(long);
  }
}


/*
 * Function name: pin
 * Description:   pins the poster to a wall
 * Arguments:     where to pin it
 * Returns:       same as move in /std/object.c
 */
int
pin(mixed dest){
  move(dest);
//  set_no_show_composite(1);
  tell_room(dest, 
    "A little Hobbit enters the room, pins a poster to the wall " +
    "and leaves again in a hurry.\n");
}



/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
