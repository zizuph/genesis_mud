inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
  set_short("noble");
  set_name("noble");
  set_pname("nobles");
  set_pshort("nobles");
	set_long(BSS("This is one of the many nobles who live in the "+
		"northern parts of Tyr. He looks like he feels that "+
		"he is above you.\n"));
	set_alignment(random(500)-250);
  default_config_npc(random(100)+50);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
