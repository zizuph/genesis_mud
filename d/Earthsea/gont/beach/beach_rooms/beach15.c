/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types 
#pragma no_clone

#include "default.h"
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

inherit SANDY;

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc("There is a tall white tree here with long green " +
        "plume-like fronds high in the air.\n");
    add_item(({"beach", "sandy beach"}),
        "The beach is warm yet rough. You feel the crunch of " +
        "broken rocks and the scratching of sand under your feet.\n");
    add_item(({"tree", "white tree", "tall tree", "tall white tree"}),
        "A single, very tall white tree juts out of the sand here.\n");
    add_item(({"frond", "fronds", "plume-like frond", "plume-like fronds",
        "green frond", "green fronds", "long frond", "long fronds",
        "green plume-like fronds", "long plume-like fronds",
        "long plume-like fronds" }),
        "The lush green fronds sprout out of the white tree high up in " +
        "the air forming what almost looks like a giant green " +
        "platform.\n");
    add_exit("beach14", "northwest");
    add_exit("beach16", "south");
}

public int
climb(string str)
{
    object tp = this_player();

    if(!str || !parse_command(str, this_object(),
        "[up] [the] [tall] [white] 'tree'"))
    {
        return notify_fail("Climb what?\n");
    }

    if(!tp->resolve_task(TASK_ROUTINE, ({ SS_CLIMB, TS_DEX,
        SS_ACROBAT })))
    {
        say(QCTNAME(tp) + " grasps the tall white tree and attempts " +
            "to shimmy up it, but fails to get a foothold.\n");
        write("You grasp the tall white tree and attempt to shimmy " +
            "up it, but fail to get a foothold.\n");
        return 1;
    }

    write("You grasp the tall white tree and manage to find a " +
        "foothold. Slowly you shimmy your way up to the top.\n");
    say(QCTNAME(tp) + " grasps the tall white tree and slowly " +
        "shimmies up to the top.\n");
    tp->move_living("climbing up the tree",
        "/d/Earthsea/gont/beach/beach_rooms/up_tree");
    return 1;
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(climb, "shimmy");
}
