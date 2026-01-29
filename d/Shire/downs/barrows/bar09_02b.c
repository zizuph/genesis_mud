/* A barrow passage in the downs
 * Based on Dondon's downs
 * -- Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit BAR_BASE;


void
create_barrow_room()
{
    set_short("A side passage beneath a barrow");
    set_long("@@psg_desc2@@");

    add_my_desc("A green light seems to emanate from the stones.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();

    add_exit(BAR_DIR + "bar09_02", "north");

}

void reset_shire_room()
{
    make_black_wight();
}
