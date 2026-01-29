/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("Foothills block movement in all directions except south.\n");

    AE(TROOM + "valley16", "south", 0, 1);
    reset_tant_room();
}

