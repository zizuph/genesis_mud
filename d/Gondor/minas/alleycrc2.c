/*
 *	/d/Gondor/minas/alleycrc2.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	Changed inheritance.
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
    set_circle("Second");
    set_areaname("southern");
    set_streetname("Lebennin Street");
    set_streettype("alley");
    set_activity(0);
    set_wealth(0);
    add_exit(MINAS_DIR + "s1crc2","east");
    set_extraline("The alley ends here, as a steep cliff blocks further " +
        "access to the west. To the east you see a market-square with " +
        "lots of people. A door to the south is leading into a house.");
    add_item(({"cliff","steep cliff"}), BSN(
        "The cliff is the eastern end of the Ered Nimrais, the White " +
        "Mountains which stretch out towards the east."));
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
    door->set_door_id("MT_h4_alleycrc2");
    door->set_pass_command(({"s","south"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h4r1salleycrc2");
    door->set_door_desc(BSN(
        "This wooden door is of mediocre quality. It is aged, but " +
        "bears its age well, despite the abuse it seems to have " +
        "suffered. There is a name painted on the door in the " +
        "Numenorean alphabet:") +
        "\t\tUlrad Thalion\n");
    door->set_key("MT_h4_alleycrc2");
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

