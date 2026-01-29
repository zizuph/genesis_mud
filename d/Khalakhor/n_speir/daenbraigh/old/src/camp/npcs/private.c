/*
 * Goblin village garrison - private
 * TAPAKAH 04/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/monster";
#include "../../daenbraigh.h"
#include "../../camp/camp.h"
#include "/d/Khalakhor/sys/defs.h";

inherit DAENBRAIGHPATH + "base";

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

  set_name("private");
  set_race_name("goblin");
  set_adj("fierce");
  set_long("This medium-sized goblin is a private in the goblin garrison.\n"+
	   "He looks at you fiercely, ready for battle for the goblin case.\n"+
	   "He is probably quite skilled, as the goblins invest into training\n"+
	   "of their troops.\n");
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,80,10);
  set_base_stat(SS_DEX,60,10);
  set_base_stat(SS_CON,70,10);
  set_base_stat(SS_INT,30,10);
  set_base_stat(SS_WIS,30,10);
  set_base_stat(SS_DIS,60,10);

  set_skill(SS_WEP_CLUB,50);
  set_skill(SS_DEFENSE,50);
  set_skill(SS_PARRY,50);

  add_prop(GG_SOLDIER,1);
  add_prop(GG_RANK,0);
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
  clone_object(CLUB)->move(TO);
  command("wield all");
  command("wear all");
  MONEY_MAKE_CC(BASEMONEY/2+random(BASEMONEY))->move(TO);
}
