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
    add_my_desc( "A hedge runs northeast and southeast from here. " +
        "A statue stands here as it watches over this part of " +
        "the garden, west is a magnificent tree.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
    add_item("statue", 
        "The statue is carved from marble. It is in the form of an " +
        "elven war hero.\n");
 
    add_exit( GARDEN_DIR + "tree", "west");
    add_exit( GARDEN_DIR + "path06", "northeast");
    add_exit( GARDEN_DIR + "path13", "southeast");
       
}
