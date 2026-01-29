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

    extraline = "The parlour room is the center of this burrow. " +
        "Here corridors branch off towards the kitchen and the " +
        "bedroom areas. In the middle of the western wall is a " +
        "large fireplace which provides, heat, light and " +
        "entertainment.";

    add_item(({"western wall","wall","fireplace",
                "large fireplace"}),
        "The fireplace on the western wall is lit and glowing " +
        "with the intensity of a newly lit fire.\n");


    add_exit(MICH_DIR + "burrow/2","north",0,1);
    add_exit(MICH_DIR + "burrow/2c","southeast",0,1);
    add_exit(MICH_DIR + "burrow/2f","southwest",0,1);

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
        hobbit2->set_type(CITIZEN);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }

}
