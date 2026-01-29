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
    add_my_desc( 
        "Here, you enjoy the serenity of the garden as people " +
        "pass by you. A beautiful fountain is here. You see a " +
        "tree north of here.\n\n");
   
    add_item(({"fruit", "fruits"}),
        "The trees are overloaded with various fruits, all for the " +
        "picking.\n");
    add_item("fountain",
        "The fountain is bowl shaped and sits on a pedestal. In the " +
        "the center of the fountain is a small elf, pouring water " +
        "from its urn.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);
 
    add_exit( GARDEN_DIR + "tree", "north"); 
    add_exit( GARDEN_DIR + "path14", "south");
    add_exit( GARDEN_DIR + "path12", "east");
    add_exit( GARDEN_DIR + "path10", "west");
       
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
           TP->catch_msg("You take a big drink of water from " +
               "the fountain. You feel refreshed.\n");
           say(QCTNAME(TP)+" drinks some water from the fountain.\n");
           TP->drink_soft(100);
            return 1;
        }
    else
            NF("Drink what?\n");
}
