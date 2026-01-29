#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a quit part of Altaruk.");
    street_name("Clothier");
    last_line("A door leads north into a shop.");
    
    add_item("shop", "This is the shop of Lorian the boot maker." +
        " A pair of boots have been carved into the wall above" +
        " the door.\n");
    
    add_exit(ALT_ALL + "02.c", "west", 0,1,0);
    add_exit(ALT_HOU + "boot_shop", "north", 0,1,0);
    add_exit("08.c", "east", 0,1,0);
}
