inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage bookroom");
    set_long(
	"You have entered a small study in the cottage. " +
        "Dusty leather-bound books and neatly stacked scrolls line the " +
	"shelves of this room which are built right into the walls.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);


    add_item(({"books", "book", "scroll", "scrolls"}), 
	"When you look at the books and scrolls, your eyes have " +
	"a hard time focusing.  This area must be in a state of flux.\n"
    );

    /*
     * For now the exit to the cellar is obvious.  Later it will be
     * hidden and triggered by removing a particular book.
     */
    add_prop(OBJ_I_SEARCH_TIME, 15);
    
    add_exit(TOMBDIR + "cottage_in", "east", 0);
    add_exit(TOMBDIR + "cottage_stairs", "down", 0);    
}
