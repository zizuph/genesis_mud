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

    add_my_desc("A dark mist covers the floor, obscuring your " +
        "tracks and swirling with every movement.\n");
    add_item(({"dark mist", "dark fog", "mist", "fog"}),
        "The fog muffles all sound and hides your feet. It hugs " +
        "the ground and moves about with your movements.\n");

    add_prop(ROOM_I_LIGHT, 0);
    reset_shire_room();
    
    add_exit(BAR_DIR + "bar06_03", "north");
    add_exit(BAR_DIR + "bar06_05", "south");
    add_exit(BAR_DIR + "bar06_d01", "down");



}

void reset_shire_room()
{
}
