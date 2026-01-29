inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    
    set_short("Small alley");
    
    set_long("   A dreary alley, deep in the center of Sanctuary; " +
        "dark shadows veil this confining path as the walls loom over " +
        "you, making you unsure of which direction you came from and " +
        "which direction will lead you out of these murky passageways. \n\n");
    
    add_exit("c28","east", 0, 2);
    add_exit("c32","southwest", 0, 2);
    
}
