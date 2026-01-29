#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Obsidian");
    last_line("The steps to the town hall is right north of here.");
    
    add_item("town hall", "The town hall. A useful place if you" +
        " have official business in Altaruk.\n");
    
    add_exit(ALT_HOU + "townhall", "north", 0,1,0);
    add_exit("10.c", "northwest", 0,1,0);
    add_exit("11.c", "west", 0,1,0);
    add_exit("13.c", "northeast", 0,1,0);
    add_exit("16.c", "southeast", 0,1,0);
}
