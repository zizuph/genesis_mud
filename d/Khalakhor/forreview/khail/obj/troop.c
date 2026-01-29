#include "/d/Immortal/std/domain.h"

inherit "/d/Immortal/stexx/obj/multi_npc";

void
create_monster()
{
  disable_commands();
  set_name("troop");
  set_pname("troops");
  add_name("troop of santas");
  add_pname("troops of santas");
  set_short("troop of santas");
  set_pshort("troops of santas");
  npcs = (["/d/Immortal/aigir/monster/santa":5]);
  create_multi();
}
