#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    extra_line("The northern part of the town. The buildings here" +
        " are erratic, many of them are nothing more than make-shift" +
        " tents. People are running carrying wares from the caravans.");
    last_line("There is a warehouse to the west.");
    
    add_exit("02", "north", 0,1,0);
    add_exit("03", "northeast", 0,1,0);
    add_exit("05", "east", 0,1,0);
}
