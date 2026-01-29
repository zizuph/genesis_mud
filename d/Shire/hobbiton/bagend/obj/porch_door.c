/*
 * Bag End door out
 * Entrance Door
 * -- Finwe, April 2020
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

create_door()
{
    ::create_door();
   
    set_door_id("be_out");
    set_pass_command(({"ns", "north"}));
    set_door_name(({"round wooden door", "door"}));
    set_door_desc("This is a large round door. It is made of wood and " +
        "painted green. There are some faint scratches on the door " +
        "which have been painted over. A brass doorknob is set in the " +
        "center of the door.\n");
    add_item(({"doorknob", "knob"}),
        "It is round and made of brass. The doorknob is set in the " +
        "center of the door and used to keep the door closed.\n");
    add_item(({"scratches", "faint scratches"}),
        "They are queer signs, scratch into the door. Their meaning is unclear.\n");
    set_other_room(BE_ROOMS + "entrance");
    set_open(0);
}
