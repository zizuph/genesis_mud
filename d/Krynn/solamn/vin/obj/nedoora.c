/* A door for the ne tower in Vkeep coded by Percy */
/* modified by Teth for new VK, Dec 4, 1996 */

#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("nedoor");
    set_pass_command(({"ne", "northeast"}));
    set_door_name(({"door", "iron door", "tower door"}));
    set_other_room(VROOM + "netower");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small and complex iron lock.\n");
    set_unlock_command("unlock");
}
