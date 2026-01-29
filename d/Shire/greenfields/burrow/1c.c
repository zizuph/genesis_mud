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

void
create_room()
{
   
    areaname  = "Greenfields"; /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 4;             /*Type of room in the smial*/
    areatype  = "hamlet";      /*Type of village*/
    smialsize = "tiny";        /*Size of the house*/
   
    extraline = "The kitchen is constantly in a state of upheaval. " +
        "A pile of dishes waits to be washed while a turkey " +
        "roasts in the oven.";

    add_item(({"dishes","pile","dish"}),
        "The pile of dishes is dirty with catsup and mustard " +
        "and in some places, dust.\n");
   
    add_item(({"turkey","oven"}),
        "The smell of a well-cooked turkey comes from the oven.\n");

    add_exit(GREEN_DIR + "burrow/1b","south",0,1);
    add_exit(GREEN_DIR + "burrow/1f","north",0,1);
   
    make_the_room();
    reset_room();
}

void
reset_room()
{
}
