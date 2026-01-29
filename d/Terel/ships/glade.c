/* This comment tells emacs to use c++-mode -*- C++ -*- */
/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo in the set_long()
*/

#include <macros.h>

#pragma save_binary
#pragma strict_types

#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

public void
create_pier()
{
    set_short("A small glade next to the river");
    set_long("This is a small glade on the western river bank. " +
	     "There is a natural landing place here for " +
	     "the small boats that travel the river. " +
	     "To the west you see a small path leaving in between " +
	     "the trees. To the northeast another path opens up. " +
	     "More space has been cleared out to the south.\n");
    
    add_item("trees", "They look very old and tall.\n");
    
    add_item("river", "It looks cold. You will not survive for very long " +
	     "if you falls into it. It goes in the northeast-southwest " +
	     "direction.");

    add_exit("/d/Terel/janus/garden/entrance", "northeast", 0);
    add_exit("/d/Terel/enchanted/path_a2", "west", 0);
    add_exit("glade2", "south", 0);
    add_pier_entry(MASTER_OB(this_object()), "Enchanted Garden", "Cabotage to Last");
    initialize_pier();
}

