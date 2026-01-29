/* hall1.c in guild, made by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit INSIDE_BASE;

void
load_board()
{
    object bb;

    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}

void
create_solace_room() 
{
    set_short("The common board");
    set_long("You are standing in a strange looking room. You are not entirely " +
	     "certain how you got here. There is nothing at all in here but a " +
	     "common board, common for everyone in Genesis.\n");

    add_exit(TDIR + "hall1", "back", 0);
    
    seteuid(getuid(TO));
    load_board();
}

