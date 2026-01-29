/* A door for the se tower in Vkeep coded by Percy */
/* modified by Teth, Dec 4, 1996 */

#include "../../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("sedoor");
    set_pass_command(({"se", "southeast"}));
    set_door_name(({"door", "iron door", "tower door"}));
    set_other_room(VROOM + "setower");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small and complex iron lock.\n");
    set_unlock_command("unlock");
}
