#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("A house has collapsed and the rubble is blocking" +
        " the way west.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
        
    add_item("rubble", "The house had seen too mush wear and" +
        " tear. It finaly gave in to gravity. Dont look like" +
        " you can get passed the remains though.\n");

    add_exit("06.c", "east", 0,1,0);
}
