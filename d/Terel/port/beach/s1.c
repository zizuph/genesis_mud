inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP              this_player()
#define TO              this_object()

#define BEACH        "/d/Terel/port/beach/"

public void
reset_room()
{
}

public void
create_room()
{
    set_short("Slippery stones");
    set_long("You are standing on a slippery stone. " +
	     "To the north is the beach, but you can also " +
	     "probably reach another stone to the southeast. " +
	     "There seems to be some kind of wreck out there.\n");
    
    add_item(({"beach"}), "It looks safer than the stones.\n");

    add_item(({"stone", "stones"}), "They are indeed slippery.\n");

    add_item(({"wreck"}), "It was a ship. It looks very old.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(BEACH + "b13", "north", 0);
    add_exit(BEACH + "s2" , "southeast", 0, 3);

    reset_room();
}
