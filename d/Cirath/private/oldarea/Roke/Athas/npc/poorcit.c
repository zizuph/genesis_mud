inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
  set_short("poor citizen");
  set_name("citizen");
  set_pname("citizens");
  set_pshort("poor citizens");
	set_long("This citizen is one of the many poor inhabitants of Tyr.\n");
	set_alignment(random(200)-50);
  default_config_npc(random(45)+50);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
