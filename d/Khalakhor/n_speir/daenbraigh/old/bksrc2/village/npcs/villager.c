/*
 * Goblin village dweller
 * TAPAKAH 04/2005
 */

inherit "/d/Khalakhor/std/monster";

#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";

inherit "../../base";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

void equip_me();
     
void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("villager");
  set_race_name("goblin");
  set_adj(VILLAGERADJ[random(sizeof(VILLAGERADJ))]);
  set_long(BS("This goblin is a typical inhabitant of the village. He looks tired "+
	      "and overworked, because the village mostly exist to support its elder "+
	      "and the military camp nearby."));
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,80,10);
  set_base_stat(SS_DEX,60,10);
  set_base_stat(SS_CON,70,10);
  set_base_stat(SS_INT,30,10);
  set_base_stat(SS_WIS,30,10);
  set_base_stat(SS_DIS,50,10);

  set_skill(SS_WEP_KNIFE,30);
  set_skill(SS_DEFENSE,50);
  set_skill(SS_UNARM_COMBAT,40);

  add_prop(GV_VILLAGER,1);
  set_alignment(VILLAGERALIGN);
  set_aggressive(0);
  set_alarm(0.5,0.0,equip_me);
  
}
void
equip_me()
{
  int i;
  int j = sizeof(VILLAGERINV);
  
  setuid();
  seteuid(getuid());

  for(i=0;i<j;i++)
    if(random(2))
      clone_object(VILLAGERINV[i])->move(TO);

  command("wield all");
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,VILLAGERFIN);
}
