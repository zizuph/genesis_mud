/* created by Aridor 12/01/93 */

inherit "/std/room";

#include "clubdefs.h"


create_room()
{
    set_short("Club Sleeping and Guest Quarters");
    set_long(BS("This is not a very large room, with beds lining the " +
		"walls. To be able to sleep here, you must get permission " +
		"first. There is a sign here with instructions to read. " +
		"",SL));

    INSIDE;
    LIGHT;

    add_item(({"bed","beds"}),
	     BS("These are very ordinary beds, rather comfortable though since " +
		"you cannot see any straw peeking out of the mattresses. " +
		"",SL));
    add_item("sign","You can read it.\n");
    add_cmd_item("sign", "read",
		 "The sign says:\n" +
		 BS("You may rent one of the beds here. To do " +
		    "this, you need to go to the squires in " +
		    "the Club Room and demand 'wake up in the " +
		    "club'. Due to cleaning and washing ex" +
		    "penses, a small fee of 10 copper coins " +
		    "(10 silver coins for non-members) will " +
		    "be charged. This fee will only cover " +
		    "the expenses for one night, so you " +
		    "will only start here once, the next " +
		    "time you log on.",SL));


    add_exit(CLUB + "club1","east");

}


