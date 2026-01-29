/*
 *	/d/Gondor/minas/n3crc2.c
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

    set_circle("Second");
    set_streetname("Anorien Street");
    set_areaname("northern");
    set_streettype("narrow alley");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "n2crc2",       "east",  0, 1);
    add_exit(MINAS_DIR + "rooms/mtarms", "south", 0, 0);
    set_extraline("This is the northern end of the Second Circle, as "
      + "the street ends in the steep cliff wall to the west. A house "
      + "north of the street is leaning with its back on the Second "
      + "Wall of the city. The alley widens out to the east. An open "
      + "doorway to the south leads into the Arms Shoppe.");

    add_item(({"wall", "walls", "second wall", "third wall", }), BSN(
        "The Second Wall is to the north, rising above a house that "
      + "was built with its back to the Second Wall. Even higher is the "
      + "Third Wall beyond the Arms Shoppe to the south. On both walls "
      + "guards are patrolling."));
    add_item("cliff", BSN("The cliff is the eastern end of the the Ered "
      + "Nimrais, the White Mountains, a mountain range which stretches "
      + "out towards the west."));
    add_item(({"house", "home", }), BSN(
        "The house was built with the back to the Second Wall from the "
      + "same rocks that were used for the city walls. A door leads "
      + "into the house."));

    if (present("door", TO))
        return;

    // clone and configure door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h5_n3crc2");
    door->set_pass_command(({"n","north"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h5r1sn3crc2");
    door->set_door_desc(BSN("The wooden door is made from massive oaken "
      + "planks expertly fitted together. "
      + "On it is written in Numenorean letters:")
      + "\t\tOrleg Belecthor\n");
    door->set_key("MT_h5_n3crc2");
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


