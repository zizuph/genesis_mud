/*
 * Daenbraigh shopkeeper
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";

inherit "/d/Khalakhor/std/monster";
inherit "../../base";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("shopkeeper");
  set_race_name("goblin");
  set_adj("plump");
  set_long(BS("This goblin is the shopkeeper of Daenbraigh. He looks at you with "+
	      "greedy eyes. It seems he has been living a better life than most of "+
	      "the inhabitants, for he is plump and well-fed.");
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

