
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"


void
create_room()
{
    set_short("Two-rivers' pier");
    set_long(break_string("A wooden pier extends out into the"
	+" waters of the River Celduin as it rushes east and south to"
	+" join nearby with the larger River Carnen.  This pier appears"
	+" to be quite old, and rot has set into the wood in places."
	+"  There is no town nearby; only the vast expanse of the"
	+" plains of northeastern Rhovanion stretching off as far as the"
	+" eye can see.  A dirt path leads away from the pier to"
	+" the north, following the bank of the River Carnen northward."
	+"\n", 75));

    add_item("sign", "There is writing on it.\n");

    add_cmd_item("sign", "read", "The sign reads: The river ship to Rhun and Esgaroth lands here.\n");

    add_exit(IH+ "near_pier", "north", 0);
}

