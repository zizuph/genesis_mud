/* 	this is a object of the volcano

    coder(s):   Deinonychus

    history:	DD.MM.YY	what done			who did
		31.03.93	created				Deinonychus

    purpose:    if you find one tell me :)

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "objects.h"
#include <stdproperties.h>

create_object()
{
    /* descriptions */

    set_name("shoe-horn");
    set_short("silver shoe-horn");
    set_long(BS("Who uses those things anyway?\n"));
    set_adj("silver");

    /* properties */

    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
} /* create_object */


/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
