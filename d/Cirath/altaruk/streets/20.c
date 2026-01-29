#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Merchant");
    extra_line("Most of the east side of the street is warehouses.");
    last_line("A road heads east towards the old fort.");
    
    add_item(({"warehouses", "warehouse"}), "The buildings on the" +
        " east side of the street are warehouses. they appear" +
        " securely locked.\n");
    
    add_item(({"fort", "old fort"}), "The old fort is in ruin from" +
        " all the attacks by the giants over the years.\n");
  
    add_exit("18.c", "north", 0,1,0);
    add_exit("19.c", "west", 0,1,0);
    add_exit("21.c", "southwest", 0,1,0);
    add_exit("22.c", "south", 0,1,0);
}
