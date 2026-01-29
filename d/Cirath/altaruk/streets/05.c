#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    street_name("Avian");
    extra_line("The northern part of the town. The buildings here" +
        " are erratic, many of them are nothing more than make-shift" +
        " tents. People are running carrying wares from the caravans.");
    last_line("The street leads southeast into the town.");
    
    add_exit("03", "north", 0,1,0);
    add_exit("02", "northwest", 0,1,0);
    add_exit("04", "west", 0,1,0);
    add_exit("06", "southeast", 0,1,0);
}
