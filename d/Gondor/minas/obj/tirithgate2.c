inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("greatgate");
  set_pass_command(({"e","east"}));
  set_door_name(({"great gate","gate","citygate"}));
  set_other_room(ANO_DIR + "pelennor/citygate");
  set_door_desc(VBFC_ME("long_desc"));
  set_lock_desc("The gate can be secured with a thick heavy wooden beam.\n");
  set_lock_name(({"beam","beams"}));
  set_lock_command("block-gate-with-beams");
  set_unlock_command("remove-beams");
  set_open(0);
  set_locked(1);
  set_key("Minas_Tirith_Key");
  set_knock_command(0);

}

string long_desc()
{
  if(open_status)
    return BSN("The iron doors of the Great Gate are open right now. " +
      "Beyond the gate you can see the road junction outside, and "+
      "the green sloping fields of Pelennor.");
  else
  {
    if(lock_status)
      return BSN("The Great Gate is closed. On your side of the gate, you " +
        "can see a thick heavy wooden beam securing the gate.");
    else
      return BSN("The Great Gate is closed right now, but the wooden beam " +
        "used to secure the gate is not in place right now. You might be " +
        "able to open the gate.");
  }
}
    

