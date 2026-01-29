/* An oak door - its lockable with a gold key (if you can find it!)        */
/* Door for cave16b.c - recoded by Tulix III, 07/08/95 */

inherit "/std/door";

#include "/d/Emerald/defs.h"

void
create_door()
{
    set_door_id("cavedoor");
    set_pass_command(({"exit","leave","go through","enter", "south"}));
    set_door_name(({"oak door","door"}));
    set_other_room(CAVE_DIR + "levelb/cave13b");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    add_prop(DOOR_I_HEIGHT, 150);
    set_open(0);
    set_locked(1);
}
