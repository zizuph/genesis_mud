inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

init()
{
     ::init();
     add_action("do_sit", "sit");
}
	  
create_room()
{
    set_short("cottage sideroom");
    set_long(
        "This side room is barren.  There is nothing in the room " +
	"other than a table with low stone benches.\n"
    );

    add_item(({"bench", "benches"}), 
	"The low stone benches are made of the same flagstone as the " +
	"floor.  They look like they would hurt your butt if you sat in " +
	"them too long.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "cottage_in", "west", 0);
}

do_sit(string what)
{
     write("The cold stone makes your rear end sore so you stand back up.\n");
     return 1;
}

