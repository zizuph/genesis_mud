/* created by Aridor 06/21/93 */

#include <macros.h>
#include "../local.h"
#include "../dragon/local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("Pier on the Vingaard River");
    set_long("Ships from all over land here occasionally. The pier looks " +
        "like it has recently been used, probably by smugglers. A sign " +
        "hangs from a pole at the waterfront and is surrounded by some " +
        "crates and barrels. The pier looks unused, surprisingly!\n");
    

    add_cmd_item("sign","read",
        "Ships from the foreign land of Faerie used to land here.\n " +
        "Captain Vilik is currently on vacation.\n"+
                 "-- Genesis ShipLines Company.\n");
    add_item("sign","You may be able to read the sign.\n");
    
    add_exit(ROOM + "pier","north");
    
    add_item("pier",BS("It looks like ships can land here.",SL));
    add_item("river",BS("This is the mighty Vingaard River. You can hardly " +
        "make out the other edge. It flows lazily to the north.",SL));
    add_item(({"barrels","crates"}),
	     "They are old and in poor condition. It doesn't look like they " +
         "are of any use anymore.\n");
         
    reset_room();
}

