inherit "/std/door";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_door()
{
    set_other_room(STAND_DIR + "path13");
    set_door_id("red door");
    set_door_name(({"door","red door","north door"}));
    set_door_desc(break_string(
	  "The red door is made of solid oak, and strengthened with "
	+ "iron bars. There is a brass lock on it.\n", 70));
    set_open_desc("There is an opened red door to the north.\n");
    set_closed_desc("There is a closed red door to the north.\n");
    set_pass_command("north");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name("brass lock");
    set_lock_desc("The red door has big brass lock on it.\n");
    set_key(KEY_TOWER2);
    set_open(0);	/* The door is initially closed */
    set_locked(1);	/* The door is initially locked */
}
