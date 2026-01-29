/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("portcullis");
    set_pass_command(({"nw","northwest","go through","out"}));
    set_fail_pass("Walking through a portcullis is a skill you haven't " +
        "mastered yet. Try opening it first.\n");
    set_door_name(({"steel portcullis","portcullis"}));
    set_other_room(ROOM + "backex");
    set_open(0);
    /*set_locked(1);   --not yet*/

}
