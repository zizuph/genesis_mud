/*
 *  /d/Emerald/common/guild/aod/rooms/blackwall_room.c
 *
 *  This is the room master for area descriptions and settings in the
 *  region of the Blackwall Mountains in Emerald in which the Army of
 *  Darkness is based.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

/* Prototypes */
public void        create_blackwall_room();
nomask void        create_emerald_room();



/*
 * Function name:        create_blackwall_room
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_blackwall_room()
{
} /* create_blackwall_room */


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room with domain presets
 */
nomask void
create_emerald_room()
{
    create_blackwall_room();
} /* create_emerald_room */


/*
 * Function name:        add_outdoor_items
 * Description  :        include add_items which are appropriate for 
 *                       outdoor areas surrounding the guild.
 */
public void
add_outdoor_items()
{
    try_item( ({ "sky", "up", "cloudy sky" }),
        "The sky overhead is dark and forboding. Wispy black clouds"
      + " coil silently over the mountain peaks drifting westward.\n");
    try_item( ({ "cloud", "clouds", "wispy cloud", "wispy clouds",
                 "black cloud", "black clouds", "wispy black cloud",
                 "wispy black clouds" }),
        "The clouds seen unnaturally dark. They almost appear to be"
      + " smoke.\n");
    try_item( ({ "smoke", "smoke cloud", "smoke clouds" }),
        "The clouds most certainly do look to be smoke. Some foul"
      + " process in the area must be belching this stuff into the"
      + " air.\n");
    try_item( ({ "mountain", "mountains", "blackwall mountains",
                 "hill", "hills" }),
        "The Blackwall Mountains are visible north, west, and east,"
      + " surrounding the area as far as the eye can see. Their"
      + " dangerous peaks and ridges rise up sharply against the"
      + " cloudy sky, making for a jagged horizon.\n");
    try_item( ({ "horizon", "peak", "peaks", "ridge", "ridges",
                 "dangerous peak", "dangerous peaks",
                 "dangerous ridge", "dangerous ridges",
                 "dangerous peaks and ridges",
                 "jagged horizon" }),
        "The ridges and peaks of the Blackwall Mountains surround" 
      + " you. They look nearly impassable.\n");
    try_item( ({ "ground", "down", "floor", "terrain",
                 "rocky terrain" }),
        "The ground is rocky and fairly uneven here.\n");
} /* add_outdoor_items */
