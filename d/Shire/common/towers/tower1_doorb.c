inherit "/std/door";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_door()
{
    set_other_room(STAND_DIR + "path13");
    set_door_id("black door");
    set_door_name(({"door","black door","south door"}));
    set_door_desc(break_string(
	  "The black door is made of solid oak, and strengthened with "
	+ "iron bars. There is an iron lock on it.\n", 70));
    set_open_desc("There is an opened black door to the south.\n");
    set_closed_desc("There is a closed black door to the south.\n");
    set_pass_command("south");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name("iron lock");
    set_lock_desc("The black door has big iron lock on it.\n");
    set_key(KEY_TOWER1);
    set_open(0);	/* The door is initially closed */
    set_locked(1);	/* The door is initially locked */
}
