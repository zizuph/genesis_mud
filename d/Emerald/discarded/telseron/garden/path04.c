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
    add_my_desc( "North takes you towards the garden entrance " +
        "and south takes you to a magnificent tree.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
 
 
    add_exit( GARDEN_DIR + "path01", "north");
    add_exit( GARDEN_DIR + "tree", "south");
    add_exit( GARDEN_DIR + "path05", "east");
    add_exit( GARDEN_DIR + "path03", "west");
       
}
