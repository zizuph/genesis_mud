#pragma strict_types

#include <macros.h>
#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor deep below the temple. " +
        "It continues to the south and on both sides of the " +
        "corridor are small doors leading to prisoner cells. To the " +
        "north is a large guard room.\n");

    add_item(({"doors", "small doors"}),
        "These are small wooden doors which lead into the cells. " + 
        "They are without locks but have a bolt to keep them shut.\n"); 
    
    add_item(({"bolt", "bolts"}),
        "The bolts are made of iron.\n");
 
    add_exit( DUNGTWO + "guard.c", "north" );
    add_exit( DUNGTWO  + "corr5.c", "south" );
    add_exit( DUNGTWO + "cell5.c", "east", "@@enter_cell", 0, 1);
    add_exit( DUNGTWO + "cell6.c", "west", "@@enter_cell", 0, 1);

}

mixed
enter_cell()
{
    write("You unbolt the door of the cell, open it and step inside.\n");
    
    say(QCTNAME(this_player()) + " unbolts the door of a cell and " +  
        "opens it.\n");
    return 0;
}

