/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */

#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/d/Shire/eastroad/smial";

void reset_room();

object hobbit1, hobbit2;

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving_burrows.txt");

    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 2;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "This parlour is much more comfortable than the " +
        "spartan entryway. Here are four cherry rocking chairs " +
        "and a few large pillows are scattered about on the " +
        "floor. The hobbits who live here must certainly enjoy " +
        "visitors. A fireplace occupies the southern wall. The " +
        "main parts of the house are north.";

    add_item(({"four chairs","cherry rocking chairs",
            "cherry rocking chair","chair"}),
        "The four cherry rocking chairs are handmade, you " +
        "suppose, judging by the glue left on the outside of " +
        "the wooden joints. Still, they must be quite " +
        "comfortable when the afternoon grows long and dinner " +
        "begins cooking.\n");

    add_item(({"fireplace","fire","fire place",
            "southern wall","wall"}),
        "The black iron fireplace cut into the southern wall is " +
        "a striking contrast to the white chalk wall it is " +
        "adjoined to. A subdued fire is kept burning by the " +
        "hobbits who live here.\n");


    add_exit(MICH_DIR + "burrow/1","north",0,1);


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
        hobbit2->set_type(TWEENS);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }


}

