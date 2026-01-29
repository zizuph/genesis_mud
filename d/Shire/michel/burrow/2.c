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
    roomtype  = 1;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "The entryhall of this smial is covered in " +
        "paintings and ornately woven carpets.  Not a spot of " +
        "bare wall or floor is to be found.  North is a room " +
        "with a large table and south, the sound of fire " +
        "crackling comes to your ears.";

    add_item("paintings",
        "The paintings are of all shapes and sizes, and any " +
        "imaginable subject-from a large painting of a small " +
        "green frog to a tiny portrait of a tall grey " +
        "wizened man.\n");

    add_item("carpets",
        "The carpets are only viewable as a whole, no " +
        "individual carpets are to be found, as they all " +
        "overlap and form a rainbow of colors and shapes for " +
        "the eye to behold.\n");

    add_exit(MICH_DIR + "gamroad2","out",0,1);
    add_exit(MICH_DIR + "burrow/2a","north",0,1);
    add_exit(MICH_DIR + "burrow/2b","south",0,1);

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
