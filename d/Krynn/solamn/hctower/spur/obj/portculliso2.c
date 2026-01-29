/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("_portcullis_2_");
    set_pass_command(({"se","southeast","enter","go through","in"}));
    set_door_name(({"steel portcullis","portcullis"}));
    set_other_room(ROOM + "hall3");
    set_open(0);
    /*set_locked(1);   --not yet*/

}
