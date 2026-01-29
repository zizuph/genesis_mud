#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Iron");
    last_line("Your west of the town hall. South you see the inn.");

    add_item("town hall", "The town hall. A useful place if you" +
        " have official business in Altaruk.\n");

    add_item("inn", "The Dead Kank, the brew there is cold and the" +
        " hospitality colder. A really nasty place. A dead insect" +
        " has been painted above the door.\n");
    
    add_exit("10.c", "north", 0,1,0);
    add_exit("12.c", "east", 0,1,0);
    add_exit(ALT_ALL + "06.c", "southwest", 0,1,0);
    add_exit(ALT_HOU + "dead_kank_inn.c", "south", 0,1,0);
}
