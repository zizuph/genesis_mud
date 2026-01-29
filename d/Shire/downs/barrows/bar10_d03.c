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
    set_short("A collapsed cavern beneath the barrow");
    set_long("@@psg_desc12@@");

    add_my_desc("\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();


    add_exit(BAR_DIR + "bar10_d02", "south");


}

void reset_shire_room()
{
    make_dark_wights();
}
