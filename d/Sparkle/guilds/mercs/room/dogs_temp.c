inherit "/std/room";

#include "../merc.h"

public void
create_room()
{
	set_short("A dog area");
	set_long("This is where dogs are stored in the mercenary "+
	     "guild.\n");

        add_exit(MROOM + "kennel", "west");
}
