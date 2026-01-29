/*
*  /d/Sparkle/area/jade/rooms/jade_house.c
*  Created 2017-01-25 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../bandit_quest_constants.h" //Room is key to evil gauntlet
#include "../defs.h"

inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Prototypes */
int leave_to_yard();
int leave_to_orchard();
object request_wheelbarrow();

/* Global variables */
static object   family1,
                family2,
                wheelbarrow;
int             backdoor_open;


/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    object door;

    set_short("The main room of a small farmhouse");
    set_long("The ground floor consists of a single large room. Light filters "
        + "in from narrow, angled slots in the wooden walls, illuminating the "
        + "narrow "
        + "beds arranged along the northern, western and southern, and down "
        + "from the second "
        + "floor, accessible via stairs along the back wall. A tall table "
        + "stands in the centre of the room. A narrow green door stands open "
        + "stands open to the west and a closed wide grey door leads east.\n");

    add_item( ({"ground", "floor", "boards", "wooden boards"}),
            "The floor is made of wooden boards, worn smooth.\n");
    add_item(({"room", "main room", "single room", "large room",
        "single large room", "here", "ground floor", "light"}),
        "The large room occupies the entire ground floor. It is dimly lit by "
        + "the light from the slots in the windowless walls, and from "
        + "upstairs.\n");
    add_item(({"slots", "slot", "narrow slot", "narrow slots"}),
        "The slots in the walls near the ceiling slant upwards and are just "
        + "wide enough to admit air and light from outside.\n");

    add_item( ({"walls", "wall", "wooden walls", "wooden wall", "logs", "log"}),
        "The walls are made of logs, stripped of bark and stained. Near the "
        + "beds, they are decorated with carvings. Narrow slots near the "
        + "ceiling allow light into the room.\n");
    add_item( ({"beds", "bed", "narrow beds", "narrow bed", "covers", "quilt",
        "quilts"}),
        "The beds are narrow and arranged along the the north, west "
        + "and south walls. Each is covered with an evenly spread quilt.");
    add_item( ({"carvings", "walls near beds", "walls near the beds",
        "decorations"}),
        "The walls around each bed are covered with images and short messages "
        + "carved into the wood: a picture of an ogre with 57 tally marks,\n"
        + "'More than knee-high? Cut before purging!',\n"
        + "'I dare you to eat a jade pear!\n");
    add_item( ({"table", "tall table", "centre", "center", "centre of room",
        "center of room", "surface", "surface of table", "tabletop"}),
        "The surface of the table is high enough to eat from while standing. "
        + "Its surface is stained with the remains of fruits and covered with "
        + "knife marks.\n");

    //Doors get in the way of NPC movement, so handling manually
    add_item( ({ "door", "first door", "narrow door", "west door", "green door",
        "doorway", "green doorway", "narrow doorway", "west doorway",
        "western door", "narrow green door", "door to the west",
        "green door to the west", "narrow door to the west" }),
        "The narrow door in the west wall stands open, leading out to "
            + "the yard. It is made of green wood and reinforced with iron. "
            + "You see no handles.\n");
    add_cmd_item( ({ "door", "first door", "narrow door", "west door", "green door",
        "doorway", "green doorway", "narrow doorway", "west doorway",
        "western door", "narrow green door", "door to the west",
        "green door to the west", "narrow door to the west" }),
        ({"open", "close", "shut"}), ({"The door is already open!\n",
            "The door will not budge!\n", "The door will not budge!\n"}) );

    add_item( ({"2nd door", "second door", "other door", "east door",
        "east doorway", "grey door", "wide door", "wide grey door",
        "eastern door", "door to east", "door to the east", "grey wide door",
        "grey door to the east"}),
        "The wide door in the eastern wall is made of grey wood, reinforced "
            + "with heavy beams. It is closed and has no handles.\n");
    add_cmd_item( ({ "door", "first door", "narrow door", "west door", "green door",
        "doorway", "green doorway", "narrow doorway", "west doorway",
        "western door", "narrow green door", "door to the west",
        "green door to the west", "narrow door to the west" }),
        ({"open", "close", "shut", "pull", "push", "ram"}),
        ({"@@leave_to_orchard", "The door is already closed!\n",
            "The door is already closed!\n", "The door has no handles!\n",
            "@@leave_to_orchard", "@@leave_to_orchard"}) );

    add_item( ({"stairs", "wooden stairs", "back wall"}),
        "The wooden stairs dominate the back "
        + "wall, leading up to a second story. The side of the stairs is "
        + "carved to resemble climbing vines.\n");

    add_exit(ROOM_DIR + "jade_yard", "west", "@@leave_to_yard");
    add_exit(ROOM_DIR + "jade_orchard_sw", "east", "@@leave_to_orchard");
    add_exit(ROOM_DIR + "jade_attic", "up");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(PATH_HOME_PROP, "!");

    reset_room();
}


/*
 * Function name: create_room
 * Description  : Populate room with NPC's.
 */
void
reset_room()
{
    string ret_text = "";
    if (!objectp(family1))
    {
        family1 = clone_object(NPC_DIR + "family.c");
        family1->set_family_index(2);
        family1->move(TO);
    }

    if (!objectp(family2))
    {
        family2 = clone_object(NPC_DIR + "family.c");
        family2->set_family_index(3);
        family2->move(TO);
    }

    request_wheelbarrow();
}


/*
 * Function name: leave_to_orchard
 * Description  : Pseudo-door exit that NPC's can see for following purposes,
 *      but not wander through. Player can pass through during quest gauntlet,
 *      which opens it to NPC's, or if done with quest.
 * Returns      : (int) Permission to leave (0) or 1 (blocked)
 */
int
leave_to_orchard()
{
    if(TP->DID_RUN_QUEST())
    {
        write("A fruit grower hurries over and strains against the wide door, "
            + "pushing it back just enough for you to slip through.\n");
        return 0;
    }
    if (!this_player()->query_npc())
    {
        if (objectp(wheelbarrow) && present( wheelbarrow, this_player() ))
        {
            write("You build up speed and ram the wide door with the "
                + "wheelbarrow.\n");
            if (present( QUEST_BURDEN, wheelbarrow ))
            {
                write("The door swings open, allowing you to careen "
                    + "through and slamming shut behind you.\n");
                return 0;
            }
            write("The door does not budge!\n");
            return 1;
        }
        write("The wide door remains closed, heavy and motionless.\n");
        return 1;
    }
    else
    { //For simplicity, NPC's never actually use the door; mobs teleport.
        return 1;
    }
}


/*
 * Function name: leave_to_yard
 * Description	: Pseudo-door exit that NPC's can see for wandering purposes.
 *   All can pass - unless player starts the evil gauntlet of the Runaway
 *   quest, in which case it is blocked.
 * Returns		: (int) Permission to leave (0) or 1 (blocked)
 */
int
leave_to_yard()
{
    if (!this_player()->query_npc())
    {
        if (present( QUEST_BURDEN, this_player() ))
        {
            write("The front door is too narrow to squeeze through "
                + "while burdened!\n");
            return 1;
        }
    }
    return 0;
}

/*
 * Function name: request_wheelbarrow
 * Description	: Ensures that a wheelbarrow is present and returns it
 * Returns		: (object) the wheelbarrow object
 */
object
request_wheelbarrow()
{
    if (!wheelbarrow | !present(wheelbarrow))
    {
        wheelbarrow = clone_object(OBJ_DIR + "wheelbarrow");
        wheelbarrow->move(this_object());
    }
    wheelbarrow->set_last_path(file_name(this_object()));
    return wheelbarrow;
}
