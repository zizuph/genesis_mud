inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("north_inwall1_door");
  set_pass_command(({"s","south"}));
  set_lock_command("lock");
  set_unlock_command("unlock");
  set_door_name(({"wooden door","door"}));
  set_other_room(MINAS_DIR + "wall/nguard1");
  set_door_desc(VBFC_ME("long_desc"));
  set_open(0);
  set_locked(1);
  set_key("Tirith_Guard_Key");
}

string long_desc()
{
  if(open_status)
  {
    return BSN("The wooden door is open, revealing a small guard room "+
      "on the other side. You can see arrow slits in the opposite wall. ");
  }
  else
  {
    return BSN("The wooden door is closed. A small sign on the rough oak "+
      "surface, reads:   Archers Guardroom. ");
  }
}



