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

object hobbit1, hobbit2;

void
create_room()
{
   
    areaname  = "Greenfields"; /*Name of village*/
    land          = "the Shire"; /*Name of land   */
    roomtype  = 3; /*Type of room in the smial   */
    areatype   = "hamlet"; /*Type of village*/
    smialsize   = "tiny"; /*Size of the house*/
   
    extraline = "Judging by the mass of hobbits inhabiting "+
    "this burrow, eating must be nearly constant.  North is the kitchen, "+
    "and south is the entryway.  A window is on the western wall.";

    add_item("wall",
        "The wall is dusty and covered in cobwebs.\n");

    add_item(({"cobwebs","cobweb","web"}),
        "The cobwebs look uninhabited.\n");

    add_item("window",
        "Looking through the window, you can see the "+areatype+
        " of "+areaname+".\n");

    add_exit(GREEN_DIR + "burrow/1c","north",0,1);
    add_exit(GREEN_DIR + "burrow/1","south",0,1);
   
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
        hobbit2->set_type(TWEENS);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
}
