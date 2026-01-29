/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("steeldoors");
    set_pass_command(({"nw","northwest"}));
    set_door_name(({"steel doors","doors"}));
    set_other_room(ROOM + "frontdoor");
    set_fail_pass("The steel doors are closed.\n");
    set_open_desc("There are open steel doors leading northwest.\n");
    set_closed_desc("There are closed steel doors leading northwest.\n");
    set_open(0);
    //set_locked(1);
    set_key(237849);

}
