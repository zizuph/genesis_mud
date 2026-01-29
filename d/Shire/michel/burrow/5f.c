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
    roomtype  = 5;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
	extraline = "This bedroom is quite messy, with clothes and "+
		"sheets and odds and ends cluttering the floor.";

	add_item(({"clothes","sheets","sheet","odds","ends","floor"}),
		"The floor is covered in the possessions of the messy " +
		"occupants of this smial.\n");

	add_exit(MICH_DIR + "burrow/5","northeast",0,1);
	add_exit(MICH_DIR + "burrow/5g","south",0,1);

    make_the_room();
    reset_room();
}

void
reset_room()
{
    if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(ELDER);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }

    if (!hobbit2)
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->set_type(TWEENS);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
}
