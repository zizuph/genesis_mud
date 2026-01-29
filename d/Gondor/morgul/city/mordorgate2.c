inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgulgate");
  set_pass_command(({"e","east"}));
  set_door_name(({"dark gate","gate","mordor gate"}));
  set_other_room(MORGUL_DIR + "city/o_egate");
  set_door_desc(BS("The dark gate is shaped like a gaping mouth "+
    "with gleaming teeth.\n"));
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_no_pick(1);
  set_key("Morgul_Key");
}
