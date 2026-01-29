inherit "/std/monster";
#include "/d/Rhovanion/defs.h"

void
create_monster()
{
  object key;

  seteuid(getuid());
  set_name("goblin");
  set_race_name("goblin");
  add_prop("_live_i_see_dark", 100);
  key = clone_object(OBJ_DIR + "steel_key");
  key->set_key("gcave_cell_no_2"); /* Setting the id of the key. */
  key->move(TO);
}

