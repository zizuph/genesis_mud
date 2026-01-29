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
    set_long("@@psg_desc2@@");

    add_my_desc("Tree roots hang from the ceiling, like dead " +
        "fingers reaching for you.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();

    add_exit(BAR_DIR + "bar06_03", "west");

}

void reset_shire_room()
{
    make_black_wight();
}
