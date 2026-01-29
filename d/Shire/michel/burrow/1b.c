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

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving_burrows.txt");

    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 3;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "A large cherry dining table is the center of " +
        "attention in this small room off the entryway. This " +
        "room is quite small and the large dining table, which could " +
        "probably accommodate a dozen or more hobbits, nearly blocks " +
        "the doorways in and out of this room. A small window is cut " +
        "into the eastern wall.";

    add_item(({"dining table","table","cherry dining table",
                "large table"}),
        "The large cherry dining table is well-polished and " +
        "seems to be in constant use by the residents of this " +
        "smial. On careful examination you notice a mustard " +
        "stain on one of the edges of the table.\n");

    add_item("window",
        "Looking through the window, you can see the " + areatype +
        " of " + areaname + ".\n");

    add_exit(MICH_DIR + "burrow/1c","north",0,1);
    add_exit(MICH_DIR + "burrow/1","south",0,1);

    make_the_room();

}

void
reset_room()
{
}
