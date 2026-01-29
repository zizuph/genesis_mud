inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    
    set_short("Dead end");
    
    set_long("   The narrow passageway comes to an end. It seems that " +
        "shadows dwell forever here and the walls that surround you keep " +
        "a wary, silent watch. These streets, marked by the absence of " +
        "moral or ethical values, offer nothing but danger and peril to " +
        "those unwise enough to travel them alone. \n\n");
    
    add_exit("c16", "north", 0, 2);
    
}

