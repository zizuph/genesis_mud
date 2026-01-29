/* 	Just a sign

    coder(s):   Deinonychus

    history:	DD.MM.YY	what done			who did
		06.03.93	created				Deinonychus

    purpose:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "objects.h"
#include "sign.h"	/* holding the mapping signdesc */
#include <stdproperties.h>

/* global variables */
string writing;	/* What's written on the sign */

create_object()
{
    /* descriptions */

    set_name("sign");
    set_pname("signs");
    set_short("sign");
    set_pshort("signs");
    set_long(BS("There's something written on it.\n"));
    writing = "You can't read what's written on the sign.\n";

    /* properties */

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_NO_GET, 1);

    /* items */
    add_cmd_item("sign", "read", "@@readit@@");
} /* create_object */

/*****************************************************************************/

/*
 * Function name: write
 * Description:   write something on the sign
 * Arguments:     what to write
 * Returns:       0/1
 */

int
write(string what)
{
   writing = signdesc[what];
   return 1;
} 

/*****************************************************************************/

/*
 * Function name: readit
 * Description:   read the sign
 * Arguments:     none
 * Returns:       what's written on sign
 */

string
readit()
{
    return writing;
}

/*****************************************************************************/

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */

