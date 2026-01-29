/*
*  /d/Sparkle/area/jade/obj/wep/jade_arrow.c
*  Created 2017-03-18 by Martin Berka on Genesis MUD
*
*/

#include <stdproperties.h>

inherit "/std/arrow";

/* Global variables */


/*
 * Function name: create_arrow
 * Description  : Constructor for arrow
 */
void
create_arrow()
{
    set_adj( ({"dry", "whittled", "green"}) );
    set_short("dry whittled arrow");
    set_projectile_id("jade_arrow");
}


/*
 * Function name: get_projectile_long
 * Description  : Custom long description of arrow.
 * Arguments    : string str     - the pseudo-item to describe. Not used in
 *                                 this routine. It's intercepted in long().
 *                object for_obj - the object trying to get the long.
 *                int num        - The number of arrows in this stack.
 * Returns      : string         - description of object or pseudo-item.
 */
string
get_projectile_long(string str, object for_obj, int num)
{
    return ("The arrow" + ((num == 1) ? " is" : "s are")
        + " made of " + ((num == 1) ? "a " : "")
        + "thin branch" + ((num == 1) ? ", " : "es, each ")
        + "stripped of twigs and whittled to a point. Though quite dry, "
        + ((num == 1) ? "it remains" : "they remain") + " faintly green. "
        + ((num == 1) ? "It is" : "Each is") + " fletched with "
        + "a grey-green feather.\n");
}
