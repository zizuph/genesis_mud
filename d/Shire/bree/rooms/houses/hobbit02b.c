/*
 * Hobbit burrow in Frogmorton
 * By Finwe, September 1998
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit;
 
void
create_room()
{
   
    areaname  = "Frogmorton";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 8;             /*corridor*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "Some paintings decorate the walls.";
 
       add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"painting", "paintings", "portrait", 
            "portraits"}),
        "The paintings are portaits of the hobbits who live " +
        "here. The hobbits in the paintings look well off and " +
        "very jolly.\n");
    add_item(({"panel", "panels"}),
        "The panels on the wall are made from pieces of fine oak. " +
        "They are polished and glow in the light.\n");
    add_item(({"oak", "oal panels"}),
        "The panels of oak are wide and beautiful. They are fine " +
        "grained and are expertly cut. The panels are polished and " +
        "glow in the light.\n");
 
    add_exit(HOUSES_DIR + "hobbit02a", "north");
    add_exit(HOUSES_DIR + "hobbit02", "south");
    add_exit(HOUSES_DIR + "hobbit02c", "east");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(MAIDEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
