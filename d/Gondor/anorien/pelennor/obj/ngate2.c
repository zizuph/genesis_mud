inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "../ngatedefs.h"

create_door()
{
  ::create_door();
  set_door_id("anoriengate");
  set_pass_command(({"n","north"}));
  set_door_name(({"great gate","gate","citygate"}));
  set_other_room(OUTGATE);
  set_door_desc(VBFC_ME("long_desc"));
  set_lock_desc("The gate can be secured with a thick heavy wooden beam.\n");
  set_lock_name(({"beam","beams"}));
  set_lock_command("block-gate-with-beams");
  set_unlock_command("remove-beams");
  set_open(0);
  set_knock_command(0);
  set_locked(1);
  set_key("Rammas_Echor_Key");

}

string long_desc()
{
  if(open_status)
    return BSN("The iron doors of the great gate are open right now. " +
      "Beyond the gate you can see the cobbled road outside, and "+
      "the green fields of Anorien.");
  else
  {
    if(lock_status)
      return BSN("The great gate is closed. On your side of the gate, you " +
        "can see a thick heavy wooden beam securing the gate.");
    else
      return BSN("The great gate is closed right now, but the wooden beam " +
        "used to secure the gate is not in place right now. You might be " +
        "able to open the gate.");
  }
}
    

