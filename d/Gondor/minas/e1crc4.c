/*
 *	/d/Gondor/minas/e1crc4.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
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
    set_circle("Fourth");
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(1);
    set_wealth(2);
    add_exit(MINAS_DIR + "e2crc4", "north",     0, 1);
    add_exit(MINAS_DIR + "gate4",  "southwest", 0, 1);
    set_extraline("To the southwest you see the Fourth Gate, which will take "+
        "you out to the Third Circle of Minas Tirith. North, the Main Street "+
        "continues, snaking and twisting its way through the City, eventually "+
        "leading to the Citadel and the White Tower in the Seventh Circle.");

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
