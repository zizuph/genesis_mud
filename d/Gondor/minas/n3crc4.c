/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public int
enter_hall()
{
    write("You pass through the mighty gates, entering the large assembly "
        + "hall inside the building.\n");
    return 0;
}

public void
create_street()
{
    set_circle("Fourth");
    set_streetname("Wainwrights' Street");
    set_areaname("northern");
    set_streettype("narrow street");
    set_activity(0);
    set_wealth(1);

    add_exit(MINAS_DIR + "n2crc4", "east",0, 1);

    set_extraline(
        "The street ends here, before the sheer slopes of the"
      + " Mindolluin to the west.");

    add_item( ({ "slopes", "sheer slopes", "mindolluin", "mountain",
                 "west", "sheer slopes of the mindolluin" }), BSN(
        "The slopes of the Mindolluin slant down to interrupt the"
      + " progress of the road to the west."));

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();


} /* create_street */

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

