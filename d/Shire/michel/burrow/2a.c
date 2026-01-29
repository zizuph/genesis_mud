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
    roomtype  = 3;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "A small dark oak dining table is stuffed into " +
        "corner of this little room off the entryway. This room " +
        "is quite small and the small oak table, which serves " +
        "at most five hobbits, is quite fitting. A small window " +
        "is cut into the eastern wall.";

    add_item(({"dining table","table","oak dining table",
                "small table"}),
        "The small dark oak dining table is heavily scratched " +
        "and stained. On careful examination you notice a bit " +
        "of honey on one of the edges of the table.\n");

    add_item(({"honey","bit of honey"}),
        "The bit of honey is dried and sticky and utterly " +
        "unappetizing.\n");

    add_item("window",
        "Looking through the window, you can see the " + areatype +
        " of " + areaname +".\n");

    add_exit(MICH_DIR + "burrow/2","south",0,1);


    make_the_room();

}
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(TWEENS);
        hobbit->set_power(100);
        hobbit->move(TO);
    }

}
