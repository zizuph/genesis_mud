inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
  
	set_name("salama");
   add_name("receptionist");
	set_race_name("elf");
   set_living_name("_petter_");
   set_short("grey haired receptionist");
	set_long(BSS("This is the receptionist at The Elfstone Tavern "+
		"and Inn. He is the one who rents out the rooms the inn "+
		"has on the second floor, usually at a pretty high price.\n"));
	set_alignment(random(500)-250);
  default_config_npc(random(100)+50);
  
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
  ::create_monster();

  NEVERKNOWN;
}
query_knight_prestige(){return -1;}
