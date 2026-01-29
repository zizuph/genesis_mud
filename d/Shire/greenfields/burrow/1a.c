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
    roomtype  = 2;             /*Type of room in the smial   */
    areatype  = "hamlet";      /*Type of village*/
    smialsize = "tiny";        /*Size of the house*/
   
    extraline = "The parlor room is much more comfortable than the "+
    "spartan entryway.  Here are seven battered rocking chairs and a "+
    "few large pillows are scattered about on the floor.  The hobbits "+
    "who live here clean up rarely.  A fireplace occupies "+
    "the southern wall.  The main parts of the burrow are north.";

    add_item(({"seven chairs","battered rocking chairs",
            "cherry rocking chair","chair"}),
        "The seven battered rocking chairs are handmade, you " +
        "suppose, judging by the glue left on the outside of the " +
        "wooden joints.  Still, they must be quite comfortable " +
        "when the afternoon grows long and dinner begins cooking.\n");

    add_item(({"fireplace","fire","fire place","southern wall","wall"}),
        "The black iron fireplace cut into the southern wall " +
        "is a striking contrast to the white chalk wall it is " +
        "adjoined to.  A subdued fire is kept burning by the " +
        "hobbits who live here.\n");
   
    add_exit(GREEN_DIR + "burrow/1","north",0,1);
  
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

