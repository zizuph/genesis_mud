inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
  set_short("slave child");
  set_name("child");
	add_name("slave");
  set_pname("slave children");
  set_pshort("slave children");
  set_long("This is the child of a slave.\n");
	set_alignment(random(100)-50);
  default_config_npc(random(5)+7);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
