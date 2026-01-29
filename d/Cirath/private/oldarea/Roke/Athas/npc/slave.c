inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
  set_short("slave");
  set_name("slave");
  set_pname("slaves");
  set_pshort("slaves");
  set_long("This is a puny slave.\n");
	set_alignment(random(200)-100);
  default_config_npc(random(50)+25);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
