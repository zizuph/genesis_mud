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
    roomtype  = 6;             /*Type of room in the smial*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "A small bed is set in the center of the smial. On one " +
        "side of the bed is a dresser.";

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
 
    add_exit(FROG_DIR + "smial04c", "north");
   
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
