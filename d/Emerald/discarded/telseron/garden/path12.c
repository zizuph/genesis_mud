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
    add_my_desc( "A hedge runs east and southwest from here. " +
        "Elves quietly pass you as they enjoy the beauty of the " +
        "garden. A magnificent tree is northwest of here.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
 
    add_exit( GARDEN_DIR + "path13", "east");
    add_exit( GARDEN_DIR + "path11", "west");
    add_exit( GARDEN_DIR + "tree", "northwest");
    add_exit( GARDEN_DIR + "path14", "southwest");
       
}
