inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    
    set_short("Back street");
    
    set_long("   Refuse lies everywhere; these dark and dirty " +
        "streets give no shelter to those who walk them, even the " +
        "darkened windows above are shuttered in fear. Faint footsteps " +
        "echo in the distance, while a scant breeze blows litter " +
        "from one side of the street to the other. \n\n");
    
    add_exit("/d/Emerald/sanctuary/o4.c","south", 0, 2);
    add_exit("c36","east", 0, 2);
    
}
