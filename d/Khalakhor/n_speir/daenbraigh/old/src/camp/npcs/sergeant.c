/*
 * Goblin village garrison - private
 * TAPAKAH 04/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/monster";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../camp/camp.h"

inherit DAENBRAIGHPATH + "base";

void equip_me();
     
void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("sergeant");
  set_race_name("goblin");
  set_adj("barrel-chested");
  set_long(BSN("This large wizened goblin is a sergeant in the goblin garrison. "+
	       "He looks at you fiercely, ready for battle for the goblin case. "+
	       "He is probably quite skilled, as the goblins invest into training "+
	       "of their troops.")
	   );
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,120,10);
  set_base_stat(SS_DEX,80,10);
  set_base_stat(SS_CON,120,10);
  set_base_stat(SS_INT,50,10);
  set_base_stat(SS_WIS,50,10);
  set_base_stat(SS_DIS,100,10);

  set_skill(SS_WEP_CLUB,75);
  set_skill(SS_DEFENSE,75);
  set_skill(SS_PARRY,75);

  add_prop(GG_SOLDIER,1);
  add_prop(GG_RANK,2);
  set_alignment(BASEALIGN+ALIGNSHFT*query_prop(GG_RANK));
  set_aggressive("@@check_aggression@@");
  set_alarm(0.5,0.0,equip_me);
}
void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(CHAINMAIL)->move(TO);
  clone_object(HELMET)->move(TO);
  clone_object(SHIELD)->move(TO);
  clone_object(CLOAK)->move(TO);
  clone_object(CLUB)->move(TO);
  command("wield all");
  command("wear all");
  MONEY_MAKE_SC(query_prop(GG_RANK)*RANKMMULT*(BASEMONEY/2+random(BASEMONEY)))->move(TO);
}
