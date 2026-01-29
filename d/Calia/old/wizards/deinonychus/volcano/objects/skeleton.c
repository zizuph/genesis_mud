/* 	A skeleton

    coder(s):   Deinonychus

    history:	DD.MM.YY	what done			who did
		08.03.93	created				Deinonychus

    purpose:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "objects.h"
#include "skeleton.h"	/* holding the mapping desc */
#include <stdproperties.h>

/* global variables */
string writing;	/* What's written on the sign */

create_object()
{
    /* descriptions */

    set_name("skeleton");
    set_pname("skeletons");
    set_short("skeleton");
    set_pshort("skeletons");
    set_long("@@long@@");
    writing = "You notice that there's something wrong.\n";

    /* properties */

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_NO_GET, 1);

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
   writing = desc[what];
   return 0;
} 

/*****************************************************************************/

/*
 * Function name: long
 * Description:   long description
 * Arguments:     none
 * Returns:       long description
 */

string
long()
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

