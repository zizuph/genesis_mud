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
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 6;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "This room is pretty bare, except for sheets spread " +
        "out on the floor.";

    add_item(({"sheet","sheets","floor"}),
        "The sheets spread out on the floor provide some sleeping " +
        "comfort.\n");
   
    add_exit(GREEN_DIR + "burrow/1f","east",0,1);

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
