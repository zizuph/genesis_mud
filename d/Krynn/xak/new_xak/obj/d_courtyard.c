/*
 *  Golden double doors leading inside to the temple
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

    set_other_room(TEMPLE + "entr_hall1");
    set_pass_command(({"e", "east"}));
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small lock plated in platinum.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
}
