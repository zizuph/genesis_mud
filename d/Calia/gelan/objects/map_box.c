/* 	this is a box in Gelan for puttings maps in

    coder(s):   Deinonychus

    history:
		25.02.93	created				Deinonychus

    purpose:    container for maps

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/container";
#include "object.h"
#include <stdproperties.h>

create_container()
{
    /* descriptions */

    set_name("box");
    set_short("cardboard box");
    set_pshort("cardboard boxes");
    set_long("If you're lucky you'll find a map of Gelan in this box.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_HEIGHT, 20);
    add_prop(CONT_I_WEIGHT, 20);
    add_prop(CONT_I_MAX_WEIGHT, 1020);
    add_prop(CONT_I_VOLUME, 10);
    add_prop(CONT_I_MAX_VOLUME, 510);
    add_prop(CONT_I_RIGID, 1);
} /* create_container */


/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
