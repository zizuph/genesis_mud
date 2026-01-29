#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Merchant");
    extra_line("Most of the east side of the street is warehouses.");
    last_line("Your right beside the Bank.");
    
    add_item(({"warehouses", "warehouse"}), "The buildings on the" +
        " east side of the street are warehouses. they appear" +
        " securely locked.\n");
    
    add_item("bank", "The 1. bank of Altaruk. Maybe the only safe" +
        " place for you money in town.\n");
    
    add_exit(ALT_HOU + "bank.c", "west", 0,1,0);
    add_exit("16.c", "north", 0,1,0);
    add_exit("18.c", "south", 0,1,0);
}
