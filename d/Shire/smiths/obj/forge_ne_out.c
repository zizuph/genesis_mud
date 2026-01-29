/*
 * NE Forge door out
 * -- Finwe, May 2002
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"

create_door()
{
    set_door_id("ne_forge");
    set_pass_command(({"sw","southwest"}));
    set_door_name(({"door","wooden door"}));
    set_other_room(SMITHSDIR_ROOMS + "test_entr");
//    set_lock_command("lock");
//    set_lock_name("lock");
//    set_unlock_command("unlock");
    set_open(1);
//    set_locked(1);
    set_door_desc("This is a wooden door leading out to the " +
        "entrance of the forges. Once closed, it will lock from " +
        "the outside, preventing anyone from entering the forge, " +
        "except for other blacksmiths. When the door is open, " +
        "anyone may freely enter the forge.\n");
//    set_pick(50);
//    set_key(333222111);
}
