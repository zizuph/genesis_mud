/*
 *  /d/Gondor/minas/w1crc6.c
 *
 *  Isildur's Street, Sixth Circle
 *
 *  Original code by Elessar (1992)
 *
 *  Last modified by Alto, 06 April 2001
 *      Added room tells and revised descriptions
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_street()
{
    set_circle("Sixth");
    set_streetname("Isildur's Street");
    set_areaname("southwestern");
    set_streettype("broad street");
    set_activity(0);
    set_wealth(2);

  add_exit(INNER_MINAS + "/s3crc6", "southeast", 0, 1);
  add_exit(INNER_MINAS + "/w2crc6", "northwest", 0, 1);

    /* This extraline is unique to each street room */

    set_extraline("The quiet street is lined by large white houses, "
        + "some with lovely gardens. In days past, this was one of "
        + "the wealthiest districts in the city. The broad street "
        + "continues northwest and southwest.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    /* These items are unique to the specific streets on this circle */

    add_sixth_circle_items();

    /* These items are unique to this room */

    add_item(({"citadel wall", "citadel"}), "To the northeast, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"garden", "gardens"}), "Some of the houses have large, "
        + "beautiful flower gardens. Many of them, however, are either "
        + "overgrown from recent neglect or barren from long vacancy. "
        + "As the city prepares for war, beauty must often be remembered, "
        + "but never forgotten in the hearts of Men.\n");
    add_item(({"wall", "walls"}), "Which one? To the southwest is the sixth wall. "
        + "To the "
        + "northeast, the Citadel wall rises behind the buildings.\n");




    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    add_sixth_circle_tells();

    /* These tells are unique to this room */

    add_tell("The sweet smell of flowers hangs in the air.\n");
    add_tell("Something scurries into the tangle of an overgrown garden.\n");
    add_tell("Footsteps echo off the faces of the large buildings.\n");


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



