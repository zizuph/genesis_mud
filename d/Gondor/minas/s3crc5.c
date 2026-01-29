/*
 *	/d/Gondor/minas/s3crc5.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	Changed inheritance.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void
create_street()
{
    set_circle("Fifth");
    set_streetname("Belfalas Street");
    set_areaname("southern");
    set_streettype("street");
    set_activity(1);
    set_wealth(2);

    add_exit(MINAS_DIR + "s2crc5",          "east",  0, 1);
    add_exit(MINAS_DIR + "houses/b_garden", "south", 0, 0);

    set_extraline("The street ends in the cliff walls of Mount "
      + "Mindolluin to the west, but continues east towards "
      + "the Sixth Gate. South of the street a path leads through "
      + "a small garden to a house.");

    add_item(({"house", "garden", }), BSN(
        "Both house and garden have been taken care of very diligently. "
      + "The inhabitants probably are not wealthy, but they must be "
      + "spending some time and effort keeping house and garden in good "
      + "shape.")); 

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

