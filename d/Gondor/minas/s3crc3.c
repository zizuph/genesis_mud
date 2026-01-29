/*
 *	/d/Gondor/minas/s3crc3.c
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
    set_streetname("Tolfalas Street");
    set_areaname("southern");
    set_streettype("narrow street");
    set_activity(1);
    set_wealth(0);

    add_exit(MINAS_DIR + "s2crc3", "east", 0);

    set_extraline("The street ends to the west in front of a " +
	"mansion beyond which the steep cliff of Mount Mindolluin " +
        "rises. The street continues east, towards the Fourth Gate.");

    add_item(({"mansion", "building", }), BSN(
        "The mansion is quite large, probably built for a wealthy merchant "
      + "and his family. But it is in poor state and desperately in need "
      + "of paint and repairs."));

    if (present("door", TO))
        return;

    // clone and configure door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h7_s3crc3");
    door->set_pass_command(({"w","west"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h7r1ss3crc3");
    door->set_door_desc(BSN("Like the house, the door has seen better times. "
      + "It must have been years since it has been painted. "
      + "On it is written in the alphabet of Numenor:")
      + "\t\tUlfast Hallacar\n");
    door->set_key("MT_h7_s3crc3");
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

