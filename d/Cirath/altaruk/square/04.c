#include "../defs.h"

inherit ALT_STD + "room.c";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("scarab",ALT_NPC+"scarab.c",5,0);
}

void
create_street()
{

    short_name("in the Merchant Plaza in Altaruk.");
    extra_line("This the central square of altaruk. Its" +
        " bustling with activity. Merchant stalls crowded" +
        " with traders and costumers haggling over trinkets" +
        " and other useless items sold here. There is a well" +
        " in middle of the square.");
    last_line("All sorts of people are here, so watch you pockets.");
    
    add_item("well", "A well stands east of you.\n");
    
    add_exit("01", "north", 0,1,0);
    add_exit("02", "northeast", 0,1,0);
    add_exit("05", "east", 0,1,0);
    add_exit("08", "southeast", 0,1,0);
    add_exit("07", "south", 0,1,0);
}
