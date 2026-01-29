inherit "/std/door";
#include "/d/Roke/common/defs.h"

create_door()
{

  set_door_id("black_door");

  set_pass_command(({"w","west"}));

  set_door_name(({"secret door","door"}));

  set_other_room(CELL_D+"hallway2");

  set_open_command("open");
  set_close_command("close");
  
  set_open_mess(({"opens the secret door.\n","The wall moves a "+
		"bit out, creating a passage to the east.\n"}));
  set_close_mess(({"closes the secret door.\n","The wall softly "+
		"moves back, closing an exit.\n"}));

  set_open(0);
  set_locked(0);
}
