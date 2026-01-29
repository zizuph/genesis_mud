#include "local.h"
inherit "/d/Krynn/std/outside_room";

void
create_krynn_room()
{
    set_short("Up in a tree");
    set_long("You are in the high branches of a tree.");
    add_exit(TDIR+"rooms/plain-20-2-Z", "down", 0, 3, 1);
    add_cmd_item(({"tree","oak","oak tree","down"}),({"climb"}),"@@climb_down@@");

    add_item(({"branches"}),"The ones you stand on are easily able to hold " +
	     "you, but you dare not climb any higher.\n");
    /*add_item(({"nest","large nest"}),"The nest is empty.\n");
    * add_search(({"nest","large nest"}), 8, PAPER, -1);
    */
}

string
climb_down()
{
    this_player()->command("down");
    return "";
}
