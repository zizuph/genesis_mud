#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("You can music coming from a window.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
        
    add_item(({"window", "music"}), "A barred window is high" +
        " up on the wall. You guess it leads to the inn." +
        " The music is not bad though.\n");

    add_exit("05.c", "west", 0,1,0);
    add_exit(ALT_STR + "11.c", "northeast", 0,1,0);
}
