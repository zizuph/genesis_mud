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
    add_my_desc( "A hedge runs northwest and southwest here. " +
        "A statue has been placed here, to watch over this part of " +
        "the garden.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");   
    add_item("statue",
        "The statue is of a lovely elven maiden, playing " +
        "her lute.\n");
    add_tell("The wind gently strums the statue's lute.\n");
 
    add_exit( GARDEN_DIR + "path12", "west");
    add_exit( GARDEN_DIR + "path08", "northwest");
       
}
