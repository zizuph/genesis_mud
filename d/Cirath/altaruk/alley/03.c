#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("A cloths-line crosses the alley abow you.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
    add_item(({"line", "cloths-line"}), "Its a rope from one" +
        " rooftop to another across the alley.\n");

    add_exit("02.c", "north", 0,1,0);
    add_exit("04.c", "south", 0,1,0);
}
