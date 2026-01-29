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

object hobbit;

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving_burrows.txt");

    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 5;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "The master bedroom of this smial is not " +
        "especially opulent or well-furnished. It has a bed in " +
        "the center of the room and a chest of drawers against " +
        "the west wall.  A doorway leads south into another bedroom.";

    add_item(({"bed","center"}),
        "The bed in the center of this master bedroom is not " +
        "especially large nor especially comfortable.\n");

    add_item(({"chest","chest of drawers","drawers",
                "west wall","wall"}),
        "The chest of drawers on the west wall is probably the " +
        "most valuable item in the smial, as it seems to be " +
        "made of exceedingly high quality oak. It is closed and " +
        "probably locked as well.\n");

    add_exit(MICH_DIR + "burrow/2g","south",0,1);
    add_exit(MICH_DIR + "burrow/2b","northeast",0,1);


    make_the_room();
    reset_room();
}

void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(ELDER);
        hobbit->set_power(100);
        hobbit->move(TO);
    }

}
