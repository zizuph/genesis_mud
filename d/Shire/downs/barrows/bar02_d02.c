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
    set_short("A collapsed dark passage beneath the barrow");
    set_long("@@psg_desc11@@");

    add_my_desc("\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();



    add_exit(BAR_DIR + "bar02_d03", "north");
    add_exit(BAR_DIR + "bar02_d01", "west");

}

void reset_shire_room()
{
    make_dark_wights();
}
