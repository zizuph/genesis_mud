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
   
    extraline = "This entryhall is long and low, some of the taller " +
        "hobbits would have to duck to enter.  Pegs line the " +
        "walls and there are two benches on either side of the " +
        "hallway.  Southwest leads to the sleeping areas of the " +
        "smial and southeast leads to the more public parts of " +
        "the burrow.";

    add_item(({"pegs","walls","peg","wall"}),
        "The wooden pegs seem to hold well in the white " +
        "chalky walls here in the White Downs.\n");

    add_item(({"bench","benches","hall","hallway"}),
        "The benches are low to the ground and made of " + 
        "maple-they line up along the hallway.\n"); 

    add_exit(MICH_DIR + "gamroad5","out",0,1);
    add_exit(MICH_DIR + "burrow/5a","southeast",0,1);
    add_exit(MICH_DIR + "burrow/5f","southwest",0,1);


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

