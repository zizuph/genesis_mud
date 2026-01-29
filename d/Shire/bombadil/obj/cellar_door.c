/*
 * Door leading upstairs to the kitchen
 * Finwe, January 2002
 */

inherit "/std/door";
#include "../local.h"
#include "/d/Shire/sys/defs.h"

create_door()
{
    set_door_id("tom_kitchen_door");
    set_pass_command(({"u","up"}));
    set_door_name(({"small door","door"}));

    set_other_room(ROOMS_DIR + "rm_kitchen");
    set_open(0);
    set_door_desc(
        "This is s small wooden door. It's set into the wall upstairs at the top of the stairs wall and looks sturdy.\n");
    set_door_name(({"door","small door"}));

}
