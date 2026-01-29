/*
*  /d/Sparkle/area/jade/obj/jade_bowstring.c
*  Created 2017-02-22 by Martin Berka on Genesis MUD
*
*/

#include <stdproperties.h>

inherit "/std/bowstring";

/* Global variables */


/*
 * Function name: create_bowstring
 * Description  : Constructor for bowstring
 */
private void
create_bowstring()
{
    set_adj(({"greenish", "sinewy"}));
    set_short("greenish sinewy bowstring");
    set_long("This bowstring is made of two strands of treated sinew, twisted "
        + "together, quite stiff - and faintly green, like the flesh of all "
        + "creatures that live in the Jade Forest.\n");
}
