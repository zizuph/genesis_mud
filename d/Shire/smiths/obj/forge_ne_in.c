/*
 * NE Forge door in
 * -- Finwe, May 2002
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"

create_door()
{
    set_door_id("ne_forge");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({"wooden door","northeast door", "ne door"}));
    set_other_room(SMITHSDIR_ROOMS + "ne_forge");
    set_lock_command("lock");
    set_lock_name("ne_door");
    set_unlock_command("unlock");
    set_open(1);
    set_locked(1);
    set_door_desc("This is a wooden door leading into the northeast " +
        "forge. The door can be closed and locked only by Blacksmiths. " +
        "This is done so they may forge in peace without any interruptions.\n");
    set_pick(101);
   set_key(9035768);
}
