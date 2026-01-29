/*
 * Hammerhands guard
 * TAPAKAH, 10/2005
 */

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

void equip_me();
void set_guard();

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("guard");
  add_name("guard");
  add_name(HH_OBJID + "_guard");
  set_race_name("goblin");
  set_adj(HH_GUARD_ADJ[random(sizeof(HH_GUARD_ADJ))]);
  set_long("This burly goblin guards the entry to the Hammerhands' "+
	   "guildhouse. You can see his huge muscles and slab-like hands, "+
	   "used to large clubs.");
  set_gender(G_MALE);

  set_base_stat(SS_STR,140,10);
  set_base_stat(SS_DEX,110,10);
  set_base_stat(SS_CON,140,10);
  set_base_stat(SS_INT,60,10);
  set_base_stat(SS_WIS,60,10);
  set_base_stat(SS_DIS,120,10);

  set_skill(SS_WEP_CLUB,75);
  set_skill(SS_DEFENSE,45);
  set_skill(SS_PARRY,50);
  set_skill(SS_AWARENESS,30);

  add_prop(HH_MEMBER,HH_ACCESS_MEMBER);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_HH_GUARD);
}

void
set_guard()
{
  equip_me();
}

void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(HH_CHAINMAIL)->move(TO);
  clone_object(HH_HELMET)->move(TO);
  clone_object(HH_SHIELD)->move(TO);
  clone_object(HH_CLOAK)->move(TO);
  clone_object(HH_CLUB)->move(TO);

  command("wield all");
  command("wear all");
  MONEY_MAKE_SC(60+random(60))->move(TO);
}
