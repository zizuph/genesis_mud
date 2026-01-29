#include "../defs.h"

inherit ALT_STD + "room.c";

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
    
    add_item("well", "A well stands northeast of you.\n");
    
    add_exit(ALT_STR + "08", "west", 0,1,0);
    add_exit("04", "north", 0,1,0);
    add_exit("05", "northeast", 0,1,0);
    add_exit("08", "east", 0,1,0);
}
