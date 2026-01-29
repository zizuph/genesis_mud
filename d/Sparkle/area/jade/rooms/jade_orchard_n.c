/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_n.c
*
*  A basic orchard room - an exception in terms of its simplicity.
*
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Global variables */
object family; //NPC


/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    set_short("To the north of an orchard");
    set_long("Lush grass grows in the open area south of a sturdy, wooden "
        + "fence running east and west. While this side of the fence is full "
        + "of grass (and to the east, saplings), the ground on the north side "
        + "is scorched earth all the way to the distant trees of the Jade "
        + "Forest. "
        + "Faint paths lead in three directions, to the west and southeast "
        + "along the fence, and southwest into "
        + "a grove of more organised trees bearing a variety of fruit. Beyond "
        + "the grove, it is just possible to discern a wooden house.\n");

    add_item( ({"sapling", "saplings", "leaves"}), "Saplings grow just south "
        + "of the fence to the east. They appear to have been planted a few "
        + "years ago: the lush grass around them is even and undisturbed, "
        + "apart from a small circle around each young trunk. "
        + "Young branches bristle with leaves and will likely bear fruit this "
        + "year.\n");
    add_item( ({"branch", "branches", "leaves"}), "The branches of the "
        + "saplings are no "
        + "longer mere twigs, but could probably be broken with two hands. "
        + "They bristle with leaves.\n");
    add_item( ({"circle", "circles", "small circles", "trunks", "trunk",
        "young trunk", "young trunks"}),
        "The grass stops a handspan away from the young trunk of each "
        + "sapling. The small circle around is the trunk is kept clear of "
        + "plant life. \n");

    add_item( ({"grove", "ordered grove", "organised trees", "organized trees",
        "more organised trees", }),
        "The ordered grove of trees to the south stands in sharp contrast to "
        + "the green wall of the forest.\n");

    add_house();
    add_fence( ({"northwest", "north", "northeast"}) );
    add_forest();
    add_orchard( ({"east"}) );
    add_deadzone();

    add_exit(ROOM_DIR + "jade_orchard_w", "west");
    add_exit(ROOM_DIR + "jade_orchard_mid", "southwest");
    add_exit(ROOM_DIR + "jade_orchard_e", "southeast");
    add_exit(ROOM_DIR + "jade_orchard_mid", "south", 0, 3, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Populate room with NPC's
 */
void
reset_room()
{
    if (!objectp(family)) //Generic family, has no quest role
    {
        family = clone_object(NPC_DIR + "family.c");
        family->move(TO);
    }
}

/*
 * Function name: do_break
 * Description	: Allow the player to try to break a sapling - archer responds
 * Arguments	: (string) str - player-supplied text following the verb
 * Returns		: (int) action recognized
 */
int
do_break(string str)
{
    if (member_array(str, ({"branch", "trunk", "sapling"}) ) < 0)
    {
        return 0;
    }

    //Send arrow and message
    write("You reach for the " + str + ". ");
    find_object(ARCHER_ROOM)->send_arrow(this_player());
    switch (random(3))
    {
    case 0:
        write("That clearly is not allowed.\n");
        break;
    case 1:
        write("The owners must really care about their trees!\n");
        break;
    default:
        write("The sapling is not worth your life.\n");
    }
    return 1;
}

void
init()
{
    ::init();
    add_action(do_break, "break"); //add_cmd_item requires extra words.
    add_action(do_break, "snap"); //add_cmd_item requires extra words.
} /* init */
