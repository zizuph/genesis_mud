#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a quit part of Altaruk.");
    street_name("Clothier");
    last_line("Eastward the street opens up to the town square.");
    
    add_item(({"square", "town square"}), "To the east you can see" +
        " the town square with all its bustling activity.\n");
    
    add_exit("07.c", "west", 0,1,0);
    add_exit(ALT_SQU + "07.c", "east", 0,1,0);
}
