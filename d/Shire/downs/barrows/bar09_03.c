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
    set_short("A dark passage inside a barrow");
    set_long("@@psg_desc4@@");

    add_my_desc("\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();

    add_exit(BAR_DIR + "bar09_03a", "north");
    add_exit(BAR_DIR + "bar09_04", "east");
    add_exit(BAR_DIR + "bar09_02", "west");
    add_exit(BAR_DIR + "bar09_d01", "down");

}

void reset_shire_room()
{
    add_torch();
    make_grey_wights();
}
