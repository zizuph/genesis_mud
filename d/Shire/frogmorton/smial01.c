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
    roomtype  = 1;             /*Type of room in the smial*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "This entry hall is sparse but some paintings " +
        "hang on the walls. A few hooks are near the door for " +
        "coats and hats and the like. A bench sits in one corner.";
 
    add_item(({"bench"}),
        "The pine bench is varnished in a heavy black stain. " +
        "However, it's worn in some spots where many hobbits " +
        "have sat on it.\n");
    add_item(({"hooks", "few hooks", "hook", "brass hook", 
            "brass hooks"}),
        "There are five brass hooks set into the wall. Hats, " +
        "coats, and the like are hung on them by visitors.\n");
    add_item(({"hats", "coats", "coat", "hat"}),
        "You don't see any on the brass hooks.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"painting", "paintings", "portrait", 
            "portraits"}),
        "The paintings are portaits of the hobbits who live " +
        "here. The hobbits in the paintings look well off and " +
        "very jolly.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood and swept clean.\n");
 
    add_exit(FROG_DIR + "road01",   "out");
    add_exit(FROG_DIR + "road01",   "east", 0,0,1);    
    add_exit(FROG_DIR + "smial01b", "west");

    make_the_room();
    reset_room();
}

void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(TWEENS);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
