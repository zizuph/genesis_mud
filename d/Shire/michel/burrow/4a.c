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

object hobbit1, hobbit2;

void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 2;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "This sitting room is the center of hobbit life. " + 
        "Here stories and tales are exchanged, and rumors too, if " +
        "the truth be known.  East and west are bedrooms; the more " +
        "functional parts of the smial are south.";

    add_item("bedrooms",
        "The east bedroom seems to be the master bedroom "+
        "and the west one seems to be more of a guest room.\n");
   
    add_exit(MICH_DIR + "burrow/4","south",0,1);
    add_exit(MICH_DIR + "burrow/4g","west",0,1);
    add_exit(MICH_DIR + "burrow/4f","east",0,1);
    
    make_the_room();
    reset_room();
}

void
reset_room()
{
     if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(MAIDEN);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }
    if (!hobbit2)
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->set_type(CITIZEN);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
}