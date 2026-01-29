/* Forest near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit FORESTBASE;

public void
create_forest()
{
    add_my_desc("There is a slight disturbance in the forest litter here. " +
        "The thickness of the forest prevents movement in many " +
        "directions, except to the northwest and southeast.\n");

    AI(({"disturbance","slight disturbance"}),"The forest litter is not " +
        "as evenly placed as it should be.\n");
    AI(({"litter","forest litter"}),"It is almost as if something was " +
        "either taken away or hidden recently.\n");
    add_search(({"litter","forest litter"}),2,KRARMOUR + "green_hat", -1);

    AE(TROOM + "forest4", "northwest", 0, 2, 1);
    AE(TROOM + "forest2", "southeast", 0, 2, 1);

    reset_tant_room();
}

