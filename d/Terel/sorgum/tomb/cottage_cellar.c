inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage cellar");
    set_long(
        "Decay spreads over this musk-reeking room with its wormy " +
        "panelling, sagging floor, battered mantel and rickety furniture.  " +
        "Ceiling-high shelves of rotting volumes are on the far wall.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(TOMBDIR + "cottage_stairs", "up", 0);

    reset_room();
}

reset_room()
{
     object ob;
     
     if(!present("key"))
     {
	 ob = clone_object(TOMBDIR + "tomb_key");
	 ob->set_key(TOMB_DOOR_KEY);
	 ob->move(TO);
     }
/*     if (!present("heap")) {
          ob = clone_object(TOMBDIR + "book_heap");
          ob->move(TO);
     }
*/
     if (!present("trunk")) {
          ob = clone_object(TOMBDIR + "safe");
          ob->move(TO);
     }
}
