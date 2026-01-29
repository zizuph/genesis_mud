/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public int     check_open();

public void
create_street() 
{
    set_circle("First");
    set_areaname("northeastern");
    set_streetname("Lampwrights' Street");
    set_streettype("street");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "e3crc1", "southeast");
    add_exit(MINAS_DIR + "n2crc1", "northwest");
    add_exit(MINAS_DIR + "rooms/old_guesthouse", "north", check_open);
    set_extraline("The street turns into an alley to the northwest, but widens out "+
      "to the southeast. Upon the First Wall to the northeast you see "+
      "guards walking around, always on alert duty. The Old Guesthouse "+
      "lies to the north.");
    add_item("guards", "The guards are on alert because of the Evil One in Mordor....\n");
    add_item("wall", "The First Wall is really strong, and runs around the city in "+
	     "a wide circle. One should be safe within it.\n");
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

public int
check_open()
{
    switch (tod())
    {
    case "night":
    case "early morning":
	write("The Old Guesthouse is closed for the night.\n" +
	      "Try again in the morning.\n");
	return 1;
    default:
	return 0;
    }
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

