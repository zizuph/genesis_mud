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
   
    extraline = "This sitting room is arranged in a circular " +
        "conversational grouping; chairs, pillows, and " +
        "couches included. A fire burns merrily away in " +
        "the fireplace on the eastern wall.  Southeast is " +
        "a room for meals and northwest is the entryway.";
   
    add_item(({"chair","chairs"}),
    "The chairs are comfortably crafted of walnut.\n");

    add_item(({"pillows","pillow","couches","couch"}),
            "The sitting areas are rather colorful- red, yellow, " +
        "green and pale blue predominate.\n");
    add_item(({"fire","fireplace","eastern wall","wall"}),
        "The fireplace is discolored black from all the " +
        "ash and smoke. It has seen a fair bit of use.\n");

    add_exit(MICH_DIR + "burrow/5","northwest",0,1);
    add_exit(MICH_DIR + "burrow/5b","southeast",0,1);

    make_the_room();
    reset_room();
}

void
reset_room()
{

    if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(CITIZEN);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }

    if (!hobbit2)
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->set_type(ELDER);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
}
