/*
 *  Golden double doors.
 *  Originaly coded by Percy
 *  Revamped by Rastlin
 */
#include "../local.h"
inherit STDDOOR;

public void
create_door()
{
    set_name(({"door", "golden door", "doors", "golden doors", 
	       "double doors", "golden double doors"}));

    set_long("These double doors are made of metal and then probably " +
	     "painted golden. They look very old and very very solid " +
	     "though. The doors bear a symbol of two silver coloured " +
	     "circles joined together.\n");

    add_item(({"symbol", "symbols", "holy symbol", "circles"}), 
	     "The symbol is the holy symbol of Mishakal, two silver " +
	     "circles joined together.\n");

    set_other_room(TEMPLE + "stairs");
    set_pass_command(({"e", "east"}));
    set_fail_pass("The golden double doors are closed.\n");

    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
