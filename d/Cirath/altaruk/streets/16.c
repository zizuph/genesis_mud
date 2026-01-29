#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Merchant");
    extra_line("Most of the east side of the street is warehouses.");
    last_line("One of the warehouse appear to be open here.");
    
    add_item("Warehouses", "The buildings on the east side of the" +
        " street are warehouses. they appear securely locked." +
        " Except maybe the one directly east of you.\n");
    
    add_item("warehouse", "The warehouse east of you looks" +
        " open. Maybe you can have a look inside?\n");
    
    add_exit(ALT_HOU + "ware2.c", "east", 0,1,0);
    add_exit("12.c", "northwest", 0,1,0);
    add_exit("17.c", "south", 0,1,0);
}
