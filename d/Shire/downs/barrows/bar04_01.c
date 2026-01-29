/* A barrow passage in the downs
 * Based on Dondon's downs
 * -- Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>

inherit BAR_BASE;

void
create_barrow_room()
{
    set_short("Beneath a barrow");
    set_long("@@psg_desc1@@\n");

    add_my_desc("Piles of dirt lay scattered where you fell into " +
        "the passage.\n");
    add_prop(ROOM_I_LIGHT, 0);    

    add_exit(BAR_DIR + "bar04_02", "south");

}
