/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("steeldoors");
    set_pass_command(({"nw","northwest","enter","go through","in"}));
    set_door_name(({"steel doors","doors"}));
    set_other_room(ROOM + "frontdoor");
    set_open(0);
    /*set_locked(1);   --not yet*/

}
