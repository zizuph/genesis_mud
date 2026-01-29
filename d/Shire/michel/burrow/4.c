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
    roomtype  = 1;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "This very small entryhall seems as if it was planned " +
        "for a closet, but later the builders decided to make it " +
        "the main entrance. This cramped room has a bench and a " +
        "few hooks above it for coats and hats and the like.";

    add_item(({"bench","hooks","hook","coat","hat"}),
        "The pine bench is varnished in a heavy black stain, and " +
        "the hooks above it are fashioned from wrought iron.  No " +
        "hats or coats are on the bench or hooks at the moment.\n");

    add_exit(MICH_DIR + "gamroad4","out",0,1);
    add_exit(MICH_DIR + "burrow/4a","north",0,1);
    add_exit(MICH_DIR + "burrow/4c","south",0,1);
   
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