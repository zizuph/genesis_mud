/*
 *      /d/Gondor/minas/e2crc3.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    General revision,
 *                              changed inheritance.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public int     check_open();

public void
create_street() 
{
    set_circle("Third");
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "tcrc3",  "north", 0);
    add_exit(MINAS_DIR + "e1crc3", "south", 0);
    add_exit(MINAS_DIR + "rooms/mtbakery", "east", check_open);
    set_extraline("The broad street continues north through a tunnel piercing "+
        "the huge out-thrust bulk of the mountain that divides the City, and "+
        "south, along the circle between the Third and the Fourth Wall. To the "+
        "east is the Minas Tirith bakery.");

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
    switch (find_object(CLOCK)->query_time_of_day())
    {
    case "morning":
    case "noon":
    case "afternoon":
        write("You enter the bakery.\n");
        return 0;
    default:
        write("The bakery is closed for the night.\n");
        return 1;
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

