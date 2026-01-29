/* A door for the sw tower in Vkeep coded by Percy */
/* Modified by Teth, Dec 5 1996 */

#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("swdoor");
    set_pass_command(({"sw", "southwest"}));
    set_door_name(({"door", "iron door", "tower door"}));
    set_other_room(VROOM + "swtower");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small and complex iron lock.\n");
    set_unlock_command("unlock");
}
