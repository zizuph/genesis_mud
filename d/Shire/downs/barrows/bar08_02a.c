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
    set_short("A side passage beneath a barrow");
    set_long("@@psg_desc1@@");

    add_my_desc("A strong feeling of evil fills the room.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();

    add_exit(BAR_DIR + "bar08_02", "south");

}

void reset_shire_room()
{
    make_black_wight();
}
