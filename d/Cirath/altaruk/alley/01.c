#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("Some stairs go up along the building.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
    
    add_item("stairs", "Some stairs lead up to a door above the shop.\n");

    add_exit("02.c", "south", 0,1,0);
    add_exit(ALT_HOU + "rentstairs.c", "up", 0,1,0);
}
