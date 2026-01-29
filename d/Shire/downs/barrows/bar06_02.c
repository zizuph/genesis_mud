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
    set_long("@@psg_desc3@@");

    add_my_desc("The barrow shudders as you walk through it.\n");

    reset_shire_room();

    add_exit(BAR_DIR + "bar06_03", "south");
    add_exit(BAR_DIR + "bar06_01", "north");

}

void reset_shire_room()
{
    make_grey_wights();
    add_torch();
}
