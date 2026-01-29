/*
 * Pier for newbie circle line via Cadu
 * Tapakah, 05/2009
*/

#include <macros.h>

#pragma save_binary
#pragma strict_types

#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

public void
create_pier ()
{
    set_short("A small glade next to the river");
    set_long("This is a small glade on the western river bank. " +
	     "There is a natural landing place here for " +
	     "the small boats that travel the river. " +
	     "The glade seems to be surrounded by trees, and the only "+
	     "exit is to the north.\n");
    
    add_item("trees", "They look very old and tall.\n");
    
    add_item("river", "It looks cold. You will not survive for very long " +
	     "if you falls into it. It goes in the northeast-southwest " +
	     "direction.");

    add_exit("glade", "north", 0);     

    add_pier_entry(MASTER_OB(this_object()), "Enchanted Garden", "Newbie Line A");
    initialize_pier();
}

