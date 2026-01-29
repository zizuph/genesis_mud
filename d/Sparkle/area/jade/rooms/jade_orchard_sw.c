/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_sw.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Prototypes */
//int leave_to_house();

/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    object door;

    set_short("By a house in an orchard");
    set_long("A two-storey house stands immediately to the east. A large "
        + "orchard extends in all other directions, dense with a dozen species "
        + "of fruit tree planted in particular pattern. The trees to the south "
        + "are either burnt or newly planted; beyond them runs a large, wooden "
        + "fence. A faint path follows the fence east.\n");

    add_item( ({"burnt trees", "burnt tree", "burned trees", "burned tree",
        "damaged trees", "stumps", "fire", "dead trunks",
        "survivors", "southern trees", "trees to south", "trees near fence" }),
        "The largest of the trees to the south are burnt - many are nothing "
        + "but dead "
        + "trunks, some of which have been converted to stumps. New "
        + "trees have been planted among the survivors.\n");
    add_item( ({"new trees", "newly planted trees", "newly-planted trees" }),
        "The newly planted trees appear healthy, but are little more than "
        + "sticks and probably several years away from bearing fruit.\n");

    add_house();
    add_fence( ({"southwest", "south", "southeast"}) );
    add_orchard( ({"north"}) );

    //add_exit(ROOM_DIR + "jade_house", "west", "@@leave_to_house");
    add_exit(ROOM_DIR + "jade_orchard_se", "east");
    add_exit(ROOM_DIR + "jade_orchard_mid", "northeast", 0, 5, 1);
    add_exit(ROOM_DIR + "jade_orchard_w", "northwest", 0, 5, 1);

    /* Back door */
    door = clone_object("/std/door");
    door->set_door_id("back_door");
    door->set_pass_command(( {"w", "west"}));
    door->set_door_name(
        ( {  "door", "front door", "west door", "doorway",
        "grey doorway", "front doorway", "west doorway", "western door",
        "reinforced door", "reinforced front door",
        "grey reinforced door", "door to the west", "grey door to the west"}));
    door->set_open_desc("There is a grey reinforced door leading into the house to the west.\n");
    door->set_closed_desc(
        "There is a closed grey reinforced door leading west.\n");
    door->set_fail_pass("The grey reinforced door is closed.\n");
    door->set_open_mess(( {"opens the grey reinforced door.\n",
            "The  grey reinforced door closes.\n"}));
    door->set_close_mess(( {"closes the  grey reinforced door.\n",
            "The  grey reinforced door closes.\n"}));
    door->set_door_desc(
        "A reinforced front door to the west leads into the house. It is made of greenish grey wood.\n");
    //door->set_other_room(ROOM_DIR + "jade_house");
    door->set_open(0);
    door->set_locked(1);
    door->move(this_object());

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

}
