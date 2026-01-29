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
   
    areaname  = "Greenfields"; /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 5;             /*Type of room in the smial*/
    areatype  = "hamlet";      /*Type of village*/
    smialsize = "tiny";        /*Size of the house*/
   
    extraline = "There are several blankets and pillows spread " +
        "out on the floor. West is another bedroom.";

    add_item(({"blanket","blankets","pillow","pillows"}),
        "There are seven blankets and nine pillows on the " +
        "floor here, and it is very untidy.\n");

    add_exit(GREEN_DIR + "burrow/1c","south",0,1);
    add_exit(GREEN_DIR + "burrow/1g","west",0,1);
   
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

