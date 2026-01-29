/*
 *  /d/Sparkle/guilds/new_merc/rooms/path1.c
 *
 *  The entrance to the Merc Guild area. A road northeast of the
 *  bridge crossing the river.
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
    set_short("on a dirt road approaching a logging camp to the"
      + " southwest");
    set_long("A large clear-cut spreads out to the southwest beyond"
      + " a river which is no longer concealed by trees. The road"
      + " travels over a bridge in that direction, leading directly"
      + " into what appears to be an old logging camp. Travelling"
      + " north will take you up toward the city.\n\n");

    try_item( ({ "city", "city of sparkle", "sparkle" }),
        "The city is a ways off to the north. You can't see much"
      + " from here.\n");
    try_item( ({ "river", RIVERNAME, RIVERNAME + " river",
                 "river " + RIVERNAME, "water" }),
        "The " + RIVERNAME + " river flows gently but steadily a short"
      + " distance to the south, where it provides an easily guarded"
      + " perimeter to the camp. A sturdy bridge spans its waters.\n");
    try_item( ({ "main road", "north", "road" }),
        "The road travels out of the trees toward the city to the"
      + " north.\n");
    try_item( ({ "southwest" }),
        "To the southwest, the road crosses a bridge and enters"
      + " the camp.\n");
    try_item( ({ "camp", "mercenary camp", "logging camp",
                 "mercenary guild", "old logging camp", "guild" }),
        "The camp is still a bit to the southwest, across the bridge.\n");
    try_item( ({ "path", }),
        "The path here travels southwest across a bridge, or north"
      + " back toward the city.\n");

    add_river_view();
    add_bridge_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("south_of_sparkle", "north");
    add_exit("path2", "southwest");

    set_no_exit_msg( ({ "north", "east", "southeast", "west",
                        "northwest" }),
        "You wander along the outskirts of the trail, but find"
      + " nothing of interest.\n");
    set_no_exit_msg( ({ "south" }),
        "Travelling south, you soon come to the edge of the river."
      + " Finding no easy way to cross, you return to the path.\n");
} /* create_merc_room */

