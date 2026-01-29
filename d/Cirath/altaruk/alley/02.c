#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("Your in an alley at the western end of clothier" +
        " street.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
    
    add_exit("01.c", "north", 0,1,0);
    add_exit("03.c", "south", 0,1,0);
    add_exit(ALT_STR + "07.c", "east", 0,1,0);
}
