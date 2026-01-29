/*
 *	/d/Gondor/minas/alleycrc4.c
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

private void    add_door();

public void
create_street()
{
    set_circle("Fourth");
    set_areaname("southern");
    set_streetname("Pelargir Street");
    set_streettype("alley");
    set_activity(1);
    set_wealth(1);
    add_exit(MINAS_DIR + "s2crc4", "east", 0, 1);
    set_extraline("The alley ends here, as a steep cliff blocks further " +
        "access to the west. To the east, Pelargir Street continues. " +
        "A door to the south is leading into a house.");
    add_item(({"cliff","steep cliff"}), BSN(
        "The cliff is the eastern end of the Ered Nimrais, the White " +
        "Mountains which stretch out towards the east."));
    add_cmd_item( ({"cliff", "steep cliff" }), "climb",
	"The cliff is just too steep for you to climb.\n");
    add_item(({"house", "mansion", "residence", }), BSN(
        "This is one of the houses where the citizens of Minas Tirith "
      + "dwell. It might be the home of a small family, though certainly "
      + "not of a wealthy one."));

    add_door();

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

private void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h8_alleycrc4");
    door->set_pass_command(({"s","south"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h8r1salleycrc4");
    door->set_door_desc(BSN(
        "This door is made of a white wood. It seems to have " +
        "been crafted recently, as the pine wood is still fragrant. " +
        "There is a name painted on the door in the Numenorean " +
        "alphabet:") +
        "\t\tUlwarth Borlad\n");
    door->set_key("MT_h8_alleycrc4");
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


