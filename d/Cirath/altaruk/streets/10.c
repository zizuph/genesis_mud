#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Iron");
    last_line("Your west of the town hall.");
    
    add_item("town hall", "The town hall. A useful place if you" +
        " have official business in Altaruk.\n");
    
    add_exit("09.c", "north", 0,1,0);
    add_exit("11.c", "south", 0,1,0);
    add_exit("12.c", "southeast", 0,1,0);
}
