#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Giant");
    last_line("West the street opens up to the town square.");
    
    add_item(({"square", "town square"}), "To the west you can see" +
        " the town square with all its bustling activity.\n");
    
    add_exit(ALT_SQU + "06.c", "west", 0,1,0);
    add_exit("25.c", "east", 0,1,0);
}
