/*
 * Cave entrance to vampire guild
 * Louie 2006
 */
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define CRYPT_ROOM (VAMP_ROOM_DIR+"manor/crypt")

//proto
int do_climb(string str);

void
create_vamp_room()
{
    set_short("cave");
    set_long("You are deep within a cave in the cliff rock.  "+
        "To the west a tunnel leads towards the soft sounds of "+
        "water.  "+
        "At the bottom of the east wall of the cave is a large "+
        "hole.  "+
        "\n");

    add_item(({"hole","large hole","down","ground"}),
        "The hole in the ground looks large enough for a horse "+
        "to fall through.  For some reason the darkness of the "+
        "hole seems ominous.\n");

    add_item(({"east wall","wall","walls"}), 
        "The walls of the cave are all solid rock, although "+
        "at the bottom of the east wall is a large hole.\n");

    add_item(({"cave"}),
        "You are standing within a cave deep in the cliff rock.\n");
    
    add_item(({"cliff", "cliff face"}),
        "The rocks of the cliff are all around you.\n");
    
    add_item(({"tunnel"}),
        "The tunnel leads west towards the sound of water.\n");

    add_exit("cave_entrance.c","west");

}

void
init() {
    ::init();
    add_action(do_climb, "enter");
    add_action(do_climb, "climb");
}

int do_climb(string str)
{
    if (!strlen(str))
    {
        notify_fail("Enter the hole?\n");
        return 0;
    }

    if (str == "hole"
        || str =="the hole")
    {
        if (IS_MEMBER(this_player())) {
            write("You descend into the hole.\n");
            this_player()->move_living("M",CRYPT_ROOM,1,0);
            return 1;
        }

        write("You approach the hole, but are overcome with uncontrollable "+
            "fear long before you reach it.  You cannot bring yourself to "+
            "enter it.\n");
        return 1;
    }

    notify_fail("Enter the hole?\n");
    return 0;
}


