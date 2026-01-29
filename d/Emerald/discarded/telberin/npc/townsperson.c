inherit "/std/monster";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include "/d/Emerald/defs.h"
#include <macros.h>

void create_monster()
{
  set_name("townsperson");
  add_name("_telberin_townsperson");

#ifndef NO_WANDER
  set_monster_home(TELBERIN_DIR + "npc_handler");
  set_random_move(10);
  set_restrain_path(TELBERIN_DIR);
#endif
}

void attacked_by(object ob)
{
  ::attacked_by(ob);
  command("scream");
  set_alarm(1.0, 0.0, &get_assistance(ob));
}
