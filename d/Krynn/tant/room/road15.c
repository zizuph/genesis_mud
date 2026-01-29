/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The road continues to the northeast and southwest. " +
        "The walls of the city of Tantallon loom in the distance.\n");

    AI(({"city","walled city","tantallon"}),"The city of Tantallon " +
        "rests in the mountains.\n");
    AI(({"walls","walls of the city"}),"The walls of the city are built " +
        "high.\n");

    AE(TROOM + "road14", "southwest", 0, 2);
    AE(TROOM + "road16", "northeast", 0, 2);
    reset_tant_room();
}

