/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("steeldoors");
    set_pass_command(({"se","southeast","go through","out"}));
    set_door_name(({"steel doors","doors"}));
    set_other_room(ROOM + "entrance");
    set_open(0);
    set_open_desc("The steel doors are open.\n");
    set_closed_desc("The steel doors are closed.\n");
    set_fail_pass("The steel doors are closed.\n");
    //set_locked(1);
    set_key(237849);

}
