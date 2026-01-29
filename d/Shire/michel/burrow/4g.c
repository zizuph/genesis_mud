/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */

#pragma strict_types
#include "local.h"

inherit "/d/Shire/eastroad/smial";

void reset_room();

object hobbit;

void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 6;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
     extraline = "This bedroom seems unused, as if no guests " +
        "have stayed here for some time.";

   
    add_exit(MICH_DIR + "burrow/4a","east",0,1);
    make_the_room();
    reset_room();
}

void
reset_room()
{
}
