/*
 *  /d/Emerald/common/guild/aod/rooms/drop_room.c
 *
 *  This is the room master for area descriptions and settings in the
 *  drop rooms for the Army of Darkness.
 *
 *  Copyright (c) December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h";

inherit "/d/Emerald/std/room";
inherit AOD_LIB_DIR + "add_spike";


/* Prototypes */
public void        create_drop_room();
nomask void        create_emerald_room();



/*
 * Function name:        create_drop_room
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_drop_room()
{
} /* create_drop_room */


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room with domain presets
 */
nomask void
create_emerald_room()
{
    create_drop_room();
} /* create_emerald_room */


/*
 * Function name:        add_droproom_items
 * Description  :        include add_items which are appropriate for 
 *                       cave areas surrounding the guild.
 */
public void
add_droproom_items()
{
    try_item( ({ "cave", "cavern", "area", "guild", "here", "caves",
                 "ravine", "chasm", "depths" }),
        "This is a deep natural ravine somewhere within the depths"
      + " of the Blackwall Mountains.\n");
    try_item( ({ "sky", "ceiling", "up", "roof" }),
        "High, high above, the sky peeks from between the tops of"
      + " the ravine walls.\n");
    try_item( ({ "wall", "walls", "cave wall", "cave walls",
                 "cavern wall", "cavern walls", "wall of the cavern",
                 "walls of the cavern", "rock", "rock wall",
                 "rock walls", "walls of rock", "ravine wall",
                 "ravine walls", "wall of the ravine",
                 "walls of the ravine" }),
        "Other than the switchbacks and ledge upon which you stand,"
      + " the walls of the ravine were formed by nature. They are"
      + " rough, uneven, and steep to varying degrees.\n");
    try_item( ({ "ground", "down", "floor", "terrain",
                 "rocky terrain" }),
        "Footing is very uneven here on these switchbacks.\n");
    try_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "You are deep within the Blackwall Mountains. Its hard to"
      + " get much of an appreciation for them other than the fact"
      + " that they are most definitely made of solid rock.\n");
    try_item( ({ "switchback", "switchbacks", "trail", "path",
                 "trails", "paths" }),
        "The switchbacks hug the walls of the ravine, zig-zagging"
      + " their way down into the depths.\n");
    try_item( ({ "ledge", "wide ledge" }),
        "The ledge is just to the side of the path here. It looks"
      + " like it would be just perfect for collecting objects that"
      + " might just happen to fall through a cloud of purple Darkling"
      + " magic intended to sort droproom items. Hmmm ... how did you"
      + " ever come up with that thought? The Gods are crazy!\n");
} /* add_droproom_items */