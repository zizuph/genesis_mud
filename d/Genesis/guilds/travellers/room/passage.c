#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

void
create_traveller_room() 
{
    set_short("Dark Passageway");
    set_long("The passageway is quite dark, but there is enough" +
	    " light from the entrance to see by. The passage leads" +
	    " deeper into the cliff where you see a set of carved" +
	    " stairs begin to wind upwards.\n");
    
    add_item(({ "stair", "stairs" }),
        "They have been carved from the stone.\n");
    
    add_exit("entry","west");
    add_exit("cellar", "up");
}
