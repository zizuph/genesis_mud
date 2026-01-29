/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("14door");
    set_pass_command(({"w","west","enter","go through","in"}));
    set_door_name(({"steel door","door"}));
    set_other_room(PALACE + "office14");
    set_open(0);
    set_locked(1);

}
