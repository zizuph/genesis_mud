#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

void
create_traveller_room()
{
    set_short("Traveller Guild Entry Hall");
  
    set_long("You are in the entry hall to the Traveller" +
        " guild. This isn't the actual guild, just the old" +
	" hall abandoned a while ago. A passage leads east" +
	" into the cliff.\n");
  
    add_exit("passage", "east");

    add_exit("/d/Roke/varl/atuan/cape/cove4","west");
}
