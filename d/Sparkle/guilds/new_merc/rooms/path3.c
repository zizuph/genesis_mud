/*
 *  /d/Sparkle/guilds/new_merc/rooms/path3.c
 *
 *  Within the grounds of the Mercenary Guild beside the lodge and south
 *  of the sawmill wherein players may join the guild. This room is
 *  open to non-guild members.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;


/* Prototypes */
public void        create_merc_room();


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("beside a large lodge within the grounds of"
      + " the Mercenary Guild");
    set_long("You stand on a well-trodden path beside an old logging"
      + " lodge within the grounds of the Mercenary Guild. Large doors"
      + " open onto the path here, allowing members access to the"
      + " various amenities provided within. The path winds north"
      + " toward an old sawmill which is perched along the river,"
      + " and northeast toward a bridge which leads away from"
      + " camp.\n\n");

    try_item( ({ "northeast" }),
        "The path travels northeast over a bridge and out of camp.\n");
    try_item( ({ "north" }),
        "To the north, the path winds its way toward an old sawmill"
      + " which is being guarded by a few able-looking mercenaries.\n");
    try_item( ({ "able-looking mercenary", "able-looking mercenaries" }),
        "Able indeed! If you are not already a member of this fine"
      + " establishment, perhaps within the mill you might find a new"
      + " occupation to futher you on your path to glory.\n");
    try_item( ({ "door", "doors", "large door", "large doors",
                 "lodge door", "lodge doors", "doors of the lodge",
                 "door of the lodge" }),
        "The doors of the lodge are directly to the west here. You see"
      + " a few guards peering out with a wary gleam in their eyes.\n");
    try_item( ({ "well-trodden path", "well-trod path", }),
        "The path here clearly receives a great deal of traffic,"
      + " probably at all times of the day. A busy place in a busy"
      + " camp, this.\n");

    add_river_view();
    add_bridge_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("path4", "north");
    add_exit("path2", "northeast");
    add_exit("entrance", "west", &check_merc_access(), 1, 0);

    set_no_exit_msg( ({ "east", "southeast", "south" }),
        "You wander around the camp a bit, but find no reason to"
      + " proceed in that direction.\n");
    set_no_exit_msg( ({ "southwest", "northwest" }),
        "The lodge blocks your movement in that direction.\n");
} /* create_merc_room */
