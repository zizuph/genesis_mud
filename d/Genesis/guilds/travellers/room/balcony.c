#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

void
create_traveller_room() 
{
    set_short("Balcony");
    set_long("This is the balcony of the chateau. It leads" +
	    " around the second floor to various archways which" +
	    " lead to more finely decorated rooms.\n");
    
    add_item(({ "stair", "stairs" }),
        "They are magnificently carved marble.\n");
    add_item("balcony", "It runs the length of the second floor.\n");
    
    add_exit("stairs", "down");
    add_exit("joinroom", "north");
    add_exit("train", "west", is_member);
    add_exit("library", "south");
}
