/*
 *  /d/Sparkle/guilds/new_merc/rooms/common_rack.c
 *
 *  This is the common rack room for all members of the Mercenary guild.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("the common armoury");
    set_long("This chamber appears to be an armoury. There are no"
      + " windows in this room, and the only exit is east, through"
      + " an archway that leads back to the entry hall.\n\n");

    add_item( ({ "window", "windows" }),
        "Unlike most rooms in the lodge, this one doesn't have any.\n");
    add_item( ({ "chamber", "area", "here", "room" }),
        "This room appears to be an armoury.\n");
    add_item( ({ "armoury" }),
        "Look around. You might find something useful.\n");
    add_item( ({ "something useful" }),
        "You might try looking at the weapon rack or armour stand.\n");
    add_item( ({ "exit", "arch", "archway", "east",
                 "east wall", "eastern wall",
                 "wall to the east" }),
        "The east wall opens through an archway onto the entry hall.\n");
    add_item( ({ "hall", "entry hall" }),
        "You can't see much from in here.\n");
    add_item( ({ "grounds", "grounds of the camp", "outside",
                 "camp", "camp outside" }),
        "There aren't any windows in this room, so you aren't able"
      + " to see outside.\n");
    add_item( ({ "light", "natural light", "sunlight" }),
        "This room has a bit less natural light than other places"
      + " in the lodge, due to the lack of windows. You notice a few"
      + " lanterns on the walls which are lit, however.\n");
    add_item( ({ "lamp", "lantern", "lanterns", "lamp" }),
        "In this room, they provide the light that the windows do"
      + " in other parts of the lodge.\n");

    add_cmd_item( ({ "lantern", "lanterns", "lamp", "lamps" }),
                  ({ "extinguish" }),
        "Better not do that. This room doesn't have a good source of"
      + " light otherwise.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("entry_hall", "east");

    set_no_exit_msg( ({ "northwest", "north", "northeast", "west",
                        "southeast", "southwest", "south" }),
        "The walls of the room block your path.\n");

    setuid();
    seteuid(getuid());

    room_add_object(OBJ_DIR + "neutral_weapon_rack");
    room_add_object(OBJ_DIR + "neutral_armour_rack");
    room_add_object(OBJ_DIR + "neutral_misc_rack");
} /* create_merc_room */
