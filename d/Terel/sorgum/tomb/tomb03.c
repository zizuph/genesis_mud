inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

void
create_room()
{

    /*
     * For now stairs are obvious.  Later, use awareness.
     */
     
    set_short("Inside tomb");
    set_long(
        "This rather small room contains a slate headstone which is slowly " +
	"crumbling to dust.  A hidden stairway leads downwards.\n"
    );

    add_item(({"headstone", "slate headstone"}), 
        "The slate headstone has crumbled so much that you can only make " +
	"out the last three letters of the name, which are NIR.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(TOMBDIR + "tomb02", "south", 0);
    add_exit(TOMBDIR + "tomb_stairs", "down", 0);    
}
