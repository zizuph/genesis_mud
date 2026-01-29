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
    set_short("A dark passage below the barrow");
    set_long("@@psg_desc10@@");

    add_my_desc("\n");

    reset_shire_room();


    add_prop(ROOM_I_LIGHT, 0);


    add_exit(BAR_DIR + "bar06_04", "up");
    add_exit(BAR_DIR + "bar06_d02", "east");

}

void reset_shire_room()
{
    make_dark_wights();
}
