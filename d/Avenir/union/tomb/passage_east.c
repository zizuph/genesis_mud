#pragma strict_types
#include "defs.h"

inherit "/std/room";
#include <macros.h>


public void
create_room(void)
{
    set_short("narrow passageway");
    set_long("This passage is narrow and smooth, with white walls "+
	"that rise up to a vaulted ceiling. The passage leads to the "+
	"northeast @@west_desc@@.\n");

    add_item(({"wall","walls"}),
	"They are made from smooth, stark limestone.\n");
    add_item(({"floor","ground"}), "The ground is of smooth and "+
	"continuous purplish granite.\n");
    add_item(({"slab","rock"}), "The stone slab is massive.\n");
    add_item("ceiling", "The ceiling high above is vaulted, and upon "+
	"it a painted a large mural in dark shades of blue and ochre.\n");
    add_item("mural", "It appears to be an overhead view of some "+
	"sort of maze.\n");
    add_item("maze", "The maze in the mural is complex, and seems to "+
	"weave impossibly in upon itself, defying geometry.\nWhen you "+
	"look harder at it, you can almost make out words formed by the "+
	"lines of the maze.\n");

    add_cmd_item(({"words","maze","mural"}), "read",
	"\tYour path shall be followed by the words of awakening.\n");
    add_cmd_item(({"ceiling","mural","maze","roof"}),
	({"touch","feel","reach","push","move"}),
	"The ceiling is far out of your reach.\n");
    add_cmd_item(({"slab","stone slab","the slab",
	    "the stone slab","door"}),
	({"push","pull","lift","move","break","smash","destory"}),
	"@@open_door@@");

    add_exit("pool_room", "northeast");
}

public int
west_open(void)
{
    return (member_array("west", query_exit_cmds()) != -1);
}

public string
open_door(void)
{
    if (west_open())
        return "The slab is already open.\n";

    write("You heave against the stone slab.\n");
    say(QCTNAME(TP) +" heaves against the stone slab.\n");

    PANEL->open_door();
    return "";
}

public string
west_desc(void)
{
    if (west_open())
      return "and to the west opens up into a large, circular room";

    return "and to the west is blocked by a massive slab of stone";
}
