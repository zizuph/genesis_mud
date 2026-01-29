/*
 * Daenbraigh shopkeeper
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

void equip_me();

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("shopkeeper");
  set_race_name("goblin");
  set_adj("plump");
  set_long("This goblin is the shopkeeper of Daenbraigh. He looks at you "+
	   "with greedy eyes. It seems he has been living a better life " +
	   "than most of the inhabitants, for he is plump and well-fed.\n");
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

  set_alignment(0);
  set_aggressive(0);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_CRAFTSMAN);
  
}
void
equip_me()
{
  int i;
  int j = sizeof(V_GOBLIN_INV);
  
  setuid();
  seteuid(getuid());

  for(i=0;i<j;i++)
    clone_object(V_GOBLIN_INV[i])->move(TO);

  command("wield all");
  command("wear all");
  add_prop(OBJ_M_HAS_MONEY,V_GOBLIN_MON);
}
