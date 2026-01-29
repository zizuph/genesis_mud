/*
 * Hobbit burrow in Greenfields
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */

#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"

inherit "/d/Shire/eastroad/smial";

void reset_room();

object hobbit;

void
create_room()
{
    areaname    = "Greenfields"; /*Name of village*/
    land        = "the Shire";   /*Name of land   */
    roomtype    = 1;             /*Type of room in the smial   */
    areatype    = "hamlet";      /*Type of village*/
    smialsize   = "tiny";        /*Size of the house*/
   
    extraline = "This tiny burrow is dirtier than might be expected, as "+
    "it seems a rather lot of hobbits live in this small space.  A parlour "+
    "is south and the main parts of the burrow are to the north.";

    add_item(({"space","small space","dirt","burrow"}),
        "The entryhall to this burrow is cluttered with clothing and "+
        "all other manner of hobbit possessions.  The dirt on everything "+
        "is amazing, and covers much of this small space.\n");
      
    add_exit(GREEN_DIR + "vill1","out",0,1);
    add_exit(GREEN_DIR + "burrow/1a","south",0,1);
    add_exit(GREEN_DIR + "burrow/1b","north",0,1);
   
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
