#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Giant");
    last_line("The south wall is unusualy high here.");
    
    add_item("wall", "What wall?\n");
    add_item("south wall", "The wall is higher than usual." +
        " It also semes quite new.\n");
    add_exit("25.c", "southwest", 0,1,0);
    add_exit("27.c", "east", 0,1,0);
}
