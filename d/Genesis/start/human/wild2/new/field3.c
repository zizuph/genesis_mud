/*
 * 	field3.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

void
create_wild_room()
{
    set_items_sparkle();
    set_items_field();
    set_herbs();
    
    set_short("A large field");
    set_long("You are wandering along a small dirt path, passing through " +
        "the wide fields of tall green grass which have been colourfully " +
        "decorated with dozens of wildflowers. Marching up into the sky " +
        "above you, a rugged spur of the Grey Mountains has thrust itself " +
        "deep into Sparkle valley. The mountains stretch out along the " +
        "western and northern horizon, surrounding the grassy fields all " +
        "around you. You notice that the path turns here, moving deeper " +
        "into the valley to the north, and searching for the Dark Road " +
        "that lies somewhere to the east.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field4","north");
    add_exit(THIS_DIR + "field2","east");
    add_exit(THIS_DIR + "field3", "southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "field3", "south","@@mount@@",1,1);
    add_exit(THIS_DIR + "field3", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "field3", "northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "field3", "west","@@mount@@",1,1);
    add_exit(THIS_DIR + "field5", "northeast",0,1,1);

    add_item(({"mountain spur","spur","mountainside"}),
        "The rugged mountainside which juts up into the sky before you, " +
        "is the eastern end of a mountain spur that has cut through the " +
        "middle of Sparkle valley.");
    add_item(({"mountains","mountain","grey mountains"}),
        "They Grey Mountains surround the entire Sparkle valley, including " +
        "the jagged spur that juts up immediately before you to the south.");
    add_item(({"south horizon","southern horizon","southwest horizon",
            "southwestern horizon","south","southwest"}),
        "You cannot really see much to the south except a massive " +
        "spur of the Grey Mountains.\n");
    add_item(({"path","dirt path","small dirt path","small path",
            "narrow path","narrow dirt path"}),
        "This small dirt path winds through the fields between the Diamond " +
        "River and the spur of the Grey Mountains that has thrust into " +
        "the valley nearby.");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");
    return 1;
}
/* mount */