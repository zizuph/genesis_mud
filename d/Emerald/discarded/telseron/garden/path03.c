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
    add_my_desc( "A hedge runs west and northeast from here. " +
        "Looking southeast, you see a magnificent tree.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
 
   add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
 
 
    add_exit( GARDEN_DIR + "path04", "east");
    add_exit( GARDEN_DIR + "path02", "west");
    add_exit( GARDEN_DIR + "path01", "northeast");
    add_exit( GARDEN_DIR + "tree", "southeast");
       
}
