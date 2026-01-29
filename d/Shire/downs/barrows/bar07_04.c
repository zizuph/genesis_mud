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
    set_short("A dark passage inside a barrow");
    set_long("@@psg_desc2@@");

    add_my_desc("A quiet stillness permeates the room.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();
    add_exit(BAR_DIR + "bar07_05", "north");
    add_exit(BAR_DIR + "bar07_03", "south");


}

void reset_shire_room()
{
    add_torch();
}
