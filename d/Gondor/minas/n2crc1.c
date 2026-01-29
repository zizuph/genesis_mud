/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

void    add_door();

public void
create_street()
{
    set_circle("First");
    set_areaname("northern");
    set_streetname("Lampwrights' Street");
    set_streettype("street");
    set_activity(0);
    set_wealth(1);
    add_exit(MINAS_DIR + "n1crc1","southeast");
    add_exit(MINAS_DIR + "n3crc1","west");
    set_extraline("The street turns into an alley to the west, "
      + "but continues southeast where it widens out a bit.");

    add_door();

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();


}

public void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    // clone and configue door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h1_n2crc1");
    door->set_pass_command(({"n","north"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h1r1sn2crc1");
    door->set_door_desc(BSN("The wooden door looks rather old, and it "
      + "could use some fresh paint. "
      + "On it is written in Numenorean letters:")
      + "\t\tForweg Aranrath\n");
    door->set_key("MT_h1_n2crc1");
    door->move(TO);
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


