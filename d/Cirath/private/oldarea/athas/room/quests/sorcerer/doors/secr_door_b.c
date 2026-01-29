inherit "/std/door";

#include "/d/Roke/common/defs.h"

create_door()
{
  set_door_id("celldoor");

  set_pass_command(({"u","up"}));

  set_door_name(({"secret door","door"}));

  set_other_room(HOUS_D+"livingroom");

  set_open_command("open");
  set_close_command("close");
  
  set_lock_command("lock");
  set_unlock_command("unlock");

  set_open_mess(({"opens the secret door.\n","The fireplace "+
		  "starts to move, and soon there is a opening where "+
		  "it was.\n"}));
  set_close_mess(({"cloeses the secret door.\n","The fireplace moves "+
		   "quietly back in it's old possition.\n"}));
  set_open(0);
  set_locked(1);
}
