/*
   Diamond

    common.c 
    --------

    Coded ........: April 1997
    By ...........: Kentari

    Latest update : April 1997
    By ...........: Kentari

*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit IN_BASE;

void load_board();

void
create_dim_room()
{
    set_short("The common board");
    set_long("You are standing in a strange looking room. You are not " +
	     "entirely certain how you got here. There is nothing at all " +
	     "in here but a common board, common for everyone in Genesis.\n");
    
    add_exit(DIROOM + "board", "up", 0);
    
    seteuid(getuid(TO));
    load_board();
}


void
load_board()
{
    object bb;
    
    seteuid(getuid(TO));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}
