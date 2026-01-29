#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Obsidian");
    last_line("Your east of the town hall.");
    
    add_item("town hall", "The town hall. A useful place if you" +
        " have official business in Altaruk.\n");
    
    add_exit("12.c", "southwest", 0,1,0);
    add_exit("14.c", "east", 0,1,0);
}
