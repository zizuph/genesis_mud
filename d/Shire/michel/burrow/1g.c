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
    roomtype  = 6;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "This bedroom has five separate beds in it, it " +
        "must be for the children of the family or overnight " +
        "guests. The beds are tidily ordered in a row. East is " +
        "the master bedroom.";

    add_item(({"beds","bed","five beds","row"}),
        "The row of beds is very neatly organized against the " +
        "north wall, and the beds are made up and at the " +
        "moment, empty.\n");

    add_exit(MICH_DIR + "burrow/1f","east",0,1);
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
