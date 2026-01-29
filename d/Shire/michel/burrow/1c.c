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
    roomtype  = 4;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "The kitchen is where most of the work in this " +
        "smial gets done, as is evidenced by its neat and tidy " +
        "appearance, even though it looks well used it is by no " +
        "means dirty.  What smells like a pantry is to the west, " +
        "and there seems to be a bedroom north.";

    add_exit(MICH_DIR + "burrow/1b","south",0,1);
    add_exit(MICH_DIR + "burrow/1f","north",0,1);
    add_exit(MICH_DIR + "burrow/1d","west",0,1);

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
