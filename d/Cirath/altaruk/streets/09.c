#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Iron");
    last_line("North the street opens up to the town square.");
    
    add_item(({"square", "town square"}), "To the north you can see" +
        " the town square with all its bustling activity.\n");
    
    add_exit(ALT_SQU + "08.c", "north", 0,1,0);
    add_exit("10.c", "south", 0,1,0);
}
