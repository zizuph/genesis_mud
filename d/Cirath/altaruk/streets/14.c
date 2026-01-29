#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Obsidian");
    last_line("A door leads south into a shop.");
    
    add_item("shop", "This shop is a bit strange. A sign" +
        " depicting a pot of gold hangs over the door.\n");
        
    add_exit("13.c", "west", 0,1,0);
    add_exit("15.c", "east", 0,1,0);
}
