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
    roomtype  = 5;             /*master bedroom*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "This room, although one of the larger ones in " +
        "the burrow, is not really what one would call spacious. " +
        "Some paintings decorate the walls.";

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"painting", "paintings", "portrait", 
            "portraits"}),
        "The paintings are portaits of the hobbits who live " +
        "here. The hobbits in the paintings look well off and " +
        "very jolly.\n");
 
    add_exit(HOUSES_DIR + "hobbit02b", "south");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(CITIZEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
