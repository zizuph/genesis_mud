/*
 * File Name        : pirate_start_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : The pirates start room.
 *
 */

#pragma strict_types

inherit "/d/Ansalon/std/room";

#include "../local.h"

void
create_room()
{
    set_short("Underground cave");
    set_long("You are standing inside a huge underground cave. A thick layer of hay covers "+
             "the floor, and makes it possible for people to 'start here' if they choose to. "+
             "The cave continues through a gloomy hallway to the southwest.\n");

    add_exit("pirate_center_room", "southwest");


    add_item(({"stone", "walls", "wall", "stones"}),"The walls have are "+
             "black, but in some places the water, coming from above, "+
             "has colored it grey.\n");

    add_item(({"floor", "ground"}),"The floor is fairly smoothe, a few "+
             "footprints leads from a large hole in the center of the "+
             "towards the north.\n");

    add_item(({"hay", "grass"}),"The dry hay, seems to have been dropped "+
             "in small stacks, just big enough for a normal sized person "+
             "to sleep in it.\n");
}

int
start(string str)
{
    if (str != "here") 
    {
        write("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("Ok. You will now start here.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
