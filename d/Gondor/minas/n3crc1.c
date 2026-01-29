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

void
create_street()
{
    set_circle("First");
    set_areaname("northern");
    set_streetname("Lampwrights' Street");
    set_streettype("alley");
    set_activity(1);
    set_wealth(0);
    add_exit(MINAS_DIR + "n2crc1","east");
    set_extraline("The street ends here, as a steep cliff-wall rises up to the "
      + "west. To the south you see the Second Wall above the roofs of the "
      + "houses, and to the north lies the First Wall. The alley turns into "
      + "a street to the east.");
    add_item("wall", BSN("The First Wall is to the north, and the Second Wall "
      + "can be seen over the roofs to the south. Upon both walls some guards "
      + "are posted."));
    add_item("cliff", BSN("The cliff is the eastern end of the the Ered "
      + "Nimrais, the White Mountains, a mountainrange which stretches out "
      + "towards the west."));
    add_item(({"doors"}), "There are doors opening to the west and north "
      + "of where you are standing.\n");

    add_door();

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    // clone and configure door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h2_n3crc1");
    door->set_door_name(({"worn door", "wooden door", "door", "north door", "northern door", }));
    door->set_pass_command(({"n","north"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h2r1sn3crc1");
    door->set_door_desc(BSN("This wooden door is extremely worn by use "
      + "and weather. It has been poorly maintained and bears its age "
      + "with ill ease. On it is written in Numenorean letters:")
      + "\t\tAndrog Agarwaen\n");
    door->set_key("MT_h2_n3crc1");
    door->move(TO);

    // clone and configure door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_carpenter_n3crc1");
    door->set_door_name(({"new door", "door", "west door", "western door", "wooden door", }));
    door->set_pass_command(({"w", "west"}));
    door->set_other_room(MINAS_DIR + "rooms/carpentry");
    door->set_door_desc(BSN(
        "The door is quite new and expertly crafted. Carved into "
      + "it is the picture of large dividers sitting across a saw, the "
      + "symbol of the craft of carpentry and of the craftsman "
      + "guild of carpenters."));
    door->set_key("MT_carpenter_n3crc1");
    door->set_locked(0);
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


