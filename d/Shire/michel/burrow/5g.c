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

object hobbit;

void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 6;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "This bedroom seems to be used as a spare storage "+
        "room, judging by all the things in here.";

    add_item("things",
        "The floor is covered with them.\nWhat junk!\n");
    add_item("floor",
        "It is covered with items that have spilled over from the " +
        "master bedroom.\n");

   
   add_exit(MICH_DIR + "burrow/5f","north",0,1);
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
