/*
 * Start room of rhe Halflings guild
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

#include "halflings.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>

inherit GUILD_ROOMS;

void reset_room()
{
    ::reset_room;
}

void 
create_guild_room()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    setuid();
    seteuid(getuid());

    set_short("Sleeping Chambers");
    set_long("This is the sleeping chambers of the halflings. It is quiet " +
        "and relaxing, and a favorite place where halflings come to sleep " +
        "after their long travels. Small beds are spread around the room. " +
        "Some are occupied, and snores can be heard from them. A plaque " +
        "is attached to a wall.\n");

    add_cmd_item(({"plaque", "sign"}), "read", "@@read_sign@@");

    reset_room();
    room_add_object(HALFGLD_DIR + "rack/rack");

    add_exit(HALFGLD_DIR + "rm_board", "north");
    
}

void 
init()
{
    ::init();
    add_action("start", "start");
}

int
start(string str)
{
    if(str == "here")
    {
        TP->set_default_start_location(HALFGLD_DIR + "rm_start");
        write("You will awaken here when you return.\n");
        return 1;

    }

    write("Do what?\n");
    return 1;
}

string
read_sign()
{
    return "\n\n"+
    "\t+---------------------------------------------------+\n"+
    "\t|                                                   |\n"+
    "\t|   After a long journey, you may <start here>.     |\n"+
    "\t|   You can then rest your weary body in one of     |\n"+
    "\t|   the beds and awake here.                        |\n"+
    "\t|                                                   |\n"+
    "\t+---------------------------------------------------+\n\n";
}
