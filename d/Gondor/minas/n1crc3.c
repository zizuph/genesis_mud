/*
 *	/d/Gondor/minas/n1crc3.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
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
    object  door;

    set_circle("Third");
    set_streetname("Arnor Street");
    set_areaname("northern");
    set_streettype("street");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "gate3",  "southeast", 0, 1);
    add_exit(MINAS_DIR + "n2crc3", "west",      0, 1);
    set_extraline("The street continues southeast, towards the doors of "
      + "the Third Gate, and west among the houses in the Third Circle. "
      + "The door of one of these houses is just north of here.");

    if (present("door", TO))
        return;

    // clone and configure door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h6_n1crc3");
    door->set_pass_command(({"n","north"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h6r1sn1crc3");
    door->set_door_desc(BSN("The door is in good repair and even was "
      + "painted recently, but a closer look reveals that it must have "
      + "seen already many layers of paint and that it already withstood "
      + "the weather of many winters. "
      + "On it is written in the alphabet of Numenor:")
      + "\t\tUlfang Borlad\n");
    door->set_key("MT_h6_n1crc3");
    door->move(TO);
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