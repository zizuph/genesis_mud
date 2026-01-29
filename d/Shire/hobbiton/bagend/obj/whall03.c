/*
 * Bag End door out
 * Backdoor Door
 * -- Finwe, May 2020
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

create_door()
{
    ::create_door();
   
    set_door_id("be_out");
    set_pass_command(({"s", "south"}));
    set_door_name(({"round wooden door", "door"}));
    set_door_desc("This is a large round door. It is made of wood and " +
        "painted blue. A brass doorknob is set in the center of " +
        "the door.\n");
    add_item(({"doorknob", "knob"}),
        "It is round and made of brass. The doorknob is set in the " +
        "center of the door and used to keep the door closed.\n");
    set_other_room(BE_ROOMS + "back_porch");
    set_open(0);
}
