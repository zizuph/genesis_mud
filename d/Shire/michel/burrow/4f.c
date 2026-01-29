/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */

#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"

inherit "/d/Shire/eastroad/smial";

void reset_room();

object hobbit1;

void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 5;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
   extraline = "West is a sitting room.";   
   add_exit(MICH_DIR + "burrow/4a","west",0,1);

   make_the_room();
   reset_room();
}

void
reset_room()
{
    if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(CITIZEN);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }
}
