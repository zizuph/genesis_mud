inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgulgate");
  set_pass_command(({"n","north"}));
  set_door_name(({"dark gate","gate","morgul gate"}));
  set_other_room(MORGUL_DIR + "city/o_ngate");
  set_door_desc(VBFC_ME("long_desc"));
  set_lock_desc("The gate can be secured with three thick heavy wooden beams.\n");
  set_lock_name(({"beam","beams"}));
  set_lock_command("block-gate-with-beams");
  set_unlock_command("remove-beams");
  set_open(0);
  set_locked(1);
  set_key("Morgul_Key");
  set_knock_command(0);

}

string long_desc()
{
  if(open_status)
    return BSN("The dark wings of the gate are open right now. " +
      "Beyond the gate you can see the Morgul Vale and the road leading " +
      "down towards the bridge over the Morgulduin.");
  else
  {
    if(lock_status)
      return BSN("The dark gate is closed. On your side of the gate, you " +
        "can see three thick heavy wooden beams securing the gate.");
    else
      return BSN("The dark gate is closed right now, but the wooden beams " +
        "used to secure the gate are not in place right now. You might be " +
        "able to open the gate.");
  }
}
    

