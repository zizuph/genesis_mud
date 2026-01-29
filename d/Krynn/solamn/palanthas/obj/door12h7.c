/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("12door");
    set_pass_command(({"w","west","enter","go through","in"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(PALACE + "office12");
    set_open(0);
    set_locked(1);
    set_key(52523);
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_pick(20);
}
