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
    add_my_desc( "A hedge runs northwest and southwest from here, " +
        "a lovely fountain is here, and east, you see a " +
        "tree.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item(({"hedge", "hedges"}), 
        "The hedge is scultpured in the form of green pillars. " +
        "Each pillar stands about 10 feet tall.\n");
    add_item("fountain",
        "The fountain is bowl shaped and sits on a pedestal. It's " +
        "nothing fancy. A gentle spray of water shoots up from the " +
        "center of the bowl. Small fish swim under the surface of the " +
        "water.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);
 
    add_exit( GARDEN_DIR + "tree", "east");
    add_exit( GARDEN_DIR + "path02", "northwest");
    add_exit( GARDEN_DIR + "path09", "southwest");
       
}

init()
{   
    ::init();
    add_action("drink_it",    "drink");
}
 
drink_it(string s)
{
   if(s=="water" || s=="water from fountain")
       {
           TP->catch_msg("You take a big drink of water. " +
                "You feel refreshed.\n");
           say(QCTNAME(TP)+" drinks some water from the fountain.\n");
           TP->drink_soft(100);
            return 1;
        }
    else
            NF("Drink what?\n");
}
