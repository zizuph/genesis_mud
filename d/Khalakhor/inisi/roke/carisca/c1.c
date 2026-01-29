/*
 * c1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include <stdproperties.h>
#include <terrain.h>

void
create_room()
{
    set_short("cave entrance");
    set_long("You are standing in a cave, south of what appears to be a " +
             "larger cave system. Further south you see a thick forest. " +
             "As you look into the cave, you notice that the walls are " +
             "very smooth, and thus they must have been made by skilled " +
             "dwarves. To your south, further into the woods, you hear " +
             "the noises of wild and uncontrolled animals.\n");

    add_exit("d4", "north");
    add_exit("f2", "south");
    add_exit("t", "up");

    set_terrain(TERRAIN_OUTSIDE | TERRAIN_NATURAL | TERRAIN_OPENSPACE |
        TERRAIN_ROCK);
    //add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    
}
