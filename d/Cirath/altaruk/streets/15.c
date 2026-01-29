#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Obsidian");
    last_line("A huge pile of rubble blocks the way east.");
    
    add_item("rubble", "Stuff piled together to stop you" +
        " from going east. The eastern parts of town are still" +
        " in a terrible state since the last giant raiding" +
        " party.\n");
        
    add_exit("14.c", "west", 0,1,0);
}
