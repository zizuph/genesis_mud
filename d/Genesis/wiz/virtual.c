
#pragma save_binary

#include "default.h"
#include </secure/std.h>
#include <stdproperties.h>

#define BS(message)	break_string(message, 75)

void
create_room() 
{
	set_short("Wizard island virtual center");
	set_long("Wizard island virtual center.\n" + 
		"This room does not exist!\n"  +
		"But this doesn't mean that you can't use it!\n\n" +
		"Type 'list' to get a list of available boards.\n\n");

	add_exit(THIS_DIR + "post", "post", "@@reality");
	add_exit("", "board", "@@move_board|teleledningsanka@@");

	add_default_exits();
	change_prop(ROOM_I_LIGHT, 10);
}

void
init()
{
    add_action("do_list", "list");
    ::init();
}

int
move_board(string where)
{
    string dest;

    if (where == "teleledningsanka")
	where = query_dircmd();

    if (where == "discuss")
	dest = THIS_DIR + "discuss";
    else if (where == "domain")
	dest = THIS_DIR + "domain";
    else if (where == "flame")
	dest = THIS_DIR + "flame";
    else if (where == "idea")
	dest = THIS_DIR + "idea";
    else if (where == "lpc")
	dest = THIS_DIR + "lpc";
    else if (where == "magic")
	dest = THIS_DIR + "magic";
    else if (where == "news")
	dest = THIS_DIR + "entrance";
    else if (where == "review")
	dest = "/d/Debug/debugwiz/request";
    else if (where == "human")
	dest = "/d/Genesis/start/human/town/tower";
    else if (where == "hobbit")
	dest = "/d/Genesis/start/hobbit/v/guild";
    else if (where == "dwarf")
	dest = "/d/Genesis/start/dwarf/level_2/board";
    else if (where == "goblin")
	dest = "/d/Genesis/start/goblin/caverns/quarters";
    else if (where == "elf")
	dest = "/d/Genesis/start/elf/room/vill_board";
    else if (where == "common")
	dest = "/d/Genesis/wiz/com";
    else if (where == "gamedriver")
	dest = "/d/Genesis/wiz/gamedriver";
    else if (where == "mudlib")
	dest = THIS_DIR + "mudlib";
    else if (where == "misc")
	dest = THIS_DIR + "miscellaneous";
    else
    {
	write("There is no such board available.\n");
        return 1;
    }

    reality();
    this_player()->move_living("X", dest);
    return 1;
}

int
do_list(string what)
{
    write(BS("Type 'board <choice>' to teleport to the board room of your " +
	"choice. Available locations are: discuss, domain, flame, idea, " +
        "magic, lpc, review, news, human, hobbit, dwarf, goblin, elf, " +
	"gamedriver, mudlib, misc and common.\n"));

    return 1;
}
