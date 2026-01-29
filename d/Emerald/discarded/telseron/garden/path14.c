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
    add_my_desc( "A hedge runs northwest and northeast here. " +
        "A statue has been placed here.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");   
    add_item("statue",
        "The statue is tall and regal. It is of a lovely elf " +
        "maid whose beauty surpasses anything you have ever " +
        "seen before. The features are lifelike and display " +
        "the incredible abilities of the elves to mold rock into " +
        "any object they desire. Upon close examination, you " +
        "recognize the statue, it is the Queen herself.\n");
 
    add_exit( GARDEN_DIR + "path11", "north");
    add_exit( GARDEN_DIR + "path12", "northeast");
    add_exit( GARDEN_DIR + "path10", "northwest");
       
}
