/*
 * The Garden
 * Coded Finwe
 * September 1996
 */
 
inherit "/d/Emerald/telseron/garden/garden_base.c";
#include "/d/Emerald/defs.h"
#include "garden.h"
 
void
create_garden()
{
    add_my_desc( "A hedge runs west and southeast from here. " +
        "Here, you can quietly gather your thoughts as you " +
        "enjoy the beauty of the garden. You see a magnificent tree " +
        "northeast of here.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
 
    add_exit( GARDEN_DIR + "path11", "east"); 
    add_exit( GARDEN_DIR + "path09", "west");
    add_exit( GARDEN_DIR + "tree", "northeast");
    add_exit( GARDEN_DIR + "path14", "southeast");
       
}
