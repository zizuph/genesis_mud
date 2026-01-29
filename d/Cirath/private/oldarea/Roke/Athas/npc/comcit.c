inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
  set_short("plain citizen");
  set_name("citizen");
  set_pname("citizens");
  set_pshort("plain citizens");
	set_long("This citizen is one of the many plain people in Tyr.\n");
	set_alignment(random(200)-50);
  default_config_npc(random(75)+25);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
