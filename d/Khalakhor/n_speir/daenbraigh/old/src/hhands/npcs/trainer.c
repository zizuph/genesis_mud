/*
 * Hammerhands trainer
 * TAPAKAH, 10/2005
 */

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Shire/skills.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit "/lib/skill_raise";
inherit DAENBRAIGH_NPC;

void equip_me();

void set_up_skills();
int spar(string str);

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_living_name("Rhugh");
  set_name(({"Rhugh","Rhugh","trainer","coach","master",HH_OBJID+"_trainer"}));
  set_race_name("goblin");
  set_adj(({"stocky","agile"}));
  set_gender(G_MALE);
  set_long("This goblin sits in the corner, spinning his club lovingly, "+
	   "awaiting someone to ask for his teaching.\n");

  set_base_stat(SS_STR,190,10);
  set_base_stat(SS_DEX,160,10);
  set_base_stat(SS_CON,190,10);
  set_base_stat(SS_INT,90,10);
  set_base_stat(SS_WIS,150,10);
  set_base_stat(SS_DIS,150,10);

  set_skill(SS_WEP_CLUB,100);
  set_skill(SS_DEFENSE,100);
  set_skill(SS_PARRY,60);
  set_skill(SS_AWARENESS,30);
  set_skill(SS_BLIND_COMBAT,60);
  set_skill(SS_APPR_MON,60);
  set_skill(SS_APPR_OBJ,60);
  set_skill(SS_CLIMB,60);
  set_skill(SS_HUNTING,60);
  set_skill(SS_TRADING,60);
  set_skill(SS_MENDING_WEAPONS,60);
  
  add_prop(HH_MEMBER,HH_ACCESS_COUNCIL);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_HH_NPC);
  set_up_skills();
}

void
set_up_skills()
{
  sk_add_train(SS_PARRY,"deflect enemy weapons","parry hits",0,60,-1,0);
  sk_add_train(SS_APPR_MON,"estimate your opponents","appraise enemy",0,50,-1,0);
  sk_add_train(SS_APPR_OBJ,"estimate various objects","appraise objects",0,40,-1,0);
  sk_add_train(SS_BLIND_COMBAT,"fight in the dark","fight in the dark",0,30,-1,0);
  sk_add_train(SS_CLIMB,"master trees and cliffs","climb",0,40,-1,0);
  sk_add_train(SS_HUNTING,"hunt wild game","hunt",0,40,-1,0);
  sk_add_train(SS_TRADING,"make profitable deals","trade",0,50,-1,0);
  sk_add_train(SS_MENDING_WEAPONS,"repair weapons","repair weapons",0,45,-1,0);
  
}

void
init_living()
{
  ::init_living();
  init_skill_raise();
  add_action(spar,"spar");
}

int
spar(string str)
{
  write("You start sparring with the trainer.\n");
}

void
equip_me()
{
  clone_object(HH_SCLUB)->move(TO);
  command("wield all");
}
