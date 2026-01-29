#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Avian");
    last_line("An open doorway leads east into a guard barracks.");
    
    add_exit("05", "northwest", 0,1,0);
    add_exit(ALT_HOU + "barracks1", "east", 0,1,0);
    add_exit(ALT_SQU + "01.c", "south", 0,1,0);
}
