/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
    set_door_id("14door");
    set_pass_command(({"s","south","out"}));
    set_door_name(({"steel door","door"}));
    set_door_desc("A very solid looking steel door.\n");
    set_open_mess("opens the steel door","The steel door opens.");
    set_close_mess("closes the steel door.","The steel door closes.");
    set_lock_desc("You can't seem to find a lock.\n");
    set_key("no_key");
    set_other_room(PALACE + "office13");
    set_open(0);
    set_locked(1);

}
